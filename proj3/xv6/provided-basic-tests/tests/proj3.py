import sys, os, inspect

import toolspath
from testing import Xv6Test, Xv6Build

curdir = os.path.realpath(os.path.dirname(inspect.getfile(inspect.currentframe())))
def get_description(name):
  cfile = os.path.join(curdir, 'ctests/proj3', name+'.c')
  with open(cfile, 'r') as f:
    desc = f.readline()
  desc = desc.strip()
  desc = desc[2:]
  desc = "Description:" + desc
  if desc[-2:] == '*/':
    desc = desc[:-2]
  return desc.strip()

test_values = [
  {'name': 'clone'},
  {'name': 'badclone'},
  {'name': 'join'},
]

all_tests = []
build_test = Xv6Build
for test in test_values:
  testname = test['name']

  if 'point_value' in test.keys():
    point_value = test['point_value']
  else:
    point_value = 0

  members = {
      'name': testname,
      'tester': 'ctests/proj3/' + testname + '.c',
      'description': get_description(testname),
      'timeout': 10,
      'point_value': point_value
      }
  newclass = type(testname, (Xv6Test,), members)
  all_tests.append(newclass)
  setattr(sys.modules[__name__], testname, newclass)

class usertests(Xv6Test):
  name = 'usertests'
  tester = 'ctests/proj3/usertests.c'
  description = get_description('usertests')
  timeout = 240

# To include full regression test by running usertests, uncomment the line below.
#all_tests.append(usertests)

from testing.runtests import main
main(build_test, all_tests)
