#!/usr/bin/python

from BoostBuild import Tester
import os
from string import strip, find

t = Tester()


t.set_tree("project-test4")

t.run_build_system()

t.expect_addition("bin/gcc/debug/a.obj")
t.expect_content("bin/gcc/debug/a.obj",
"""gcc/debug/include-everything
a.cpp
""")

t.expect_addition("bin/gcc/debug/a.exe")
t.expect_content("bin/gcc/debug/a.exe",
"gcc/debug/include-everything\n" +
"bin/gcc/debug/a.obj lib/bin/gcc/debug/optimization-on/b.obj\n"
)

t.expect_addition("lib/bin/gcc/debug/optimization-on/b.obj")
t.expect_content("lib/bin/gcc/debug/optimization-on/b.obj",
"""gcc/debug/include-everything/optimization-on
lib/b.cpp
""")

t.expect_addition("bin/gcc/debug/main-target-b.exe/b.exe")
t.expect_content("bin/gcc/debug/main-target-b.exe/b.exe",
"gcc/debug/define-MACROS/include-everything\n" +
"bin/gcc/debug/a.obj\n"
)


t.copy("lib/Jamfile2", "lib/Jamfile")

expected="""error: Requirements for project at 'lib' conflict with parent's.
Explanation:  link-incompatible properties <threading>single and <threading>multi
"""
t.run_build_system("--no-error-backtrace", stdout=expected, status=None)

t.copy("lib/Jamfile3", "lib/Jamfile")

t.run_build_system(status=None)
t.fail_test(find(t.stdout(), "warning: skipped build of lib/b.obj with properties") \
            != 0)

# Check that project can be skipped as well
t.copy("Jamfile4", "Jamfile")

expected="warning: skipping build of project at lib2 due to unsatisfied requirements."
t.run_build_system("rtti=on")
t.fail_test(find(t.stdout(), expected) != 0)

t.copy("lib2/Jamfile2", "lib2/Jamfile")

expected="warning: skipping build of project /mylib at lib2 due to unsatisfied\nrequirements."
t.run_build_system("rtti=on")
t.fail_test(find(t.stdout(), expected) != 0)

# We don't yet make targets depend on Jamfile, so need to start from scratch
# The following test is disabled, because of problems related to
# issue BB10

#t.set_tree("project-test4")
#t.copy("Jamfile2", "Jamfile")

#t.run_build_system()

#t.expect_addition("bin/gcc/debug/a_gcc.obj")
#t.expect_content("bin/gcc/debug/a_gcc.obj",
#"""gcc/debug
#a_gcc.cpp
#""")

#t.expect_content("bin/gcc/debug/a.exe",
#"gcc/debug\n" +
#"bin/gcc/debug/a.obj " +
#"lib/bin/gcc/debug/optimization-on/b.obj " +
#"bin/gcc/debug/a_gcc.obj\n"
#)

# Test that if we specified composite property in target reference,
# everything works OK.

t.copy("lib/Jamfile1", "lib/Jamfile")
t.copy("Jamfile5", "Jamfile")

t.run_build_system()

t.expect_addition("lib/bin/gcc/release/b.obj")

t.expect_content("bin/gcc/debug/a.exe",
"gcc/debug/include-everything\n" +
"bin/gcc/debug/a.obj lib/bin/gcc/release/b.obj\n"
)


t.cleanup()
