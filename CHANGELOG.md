# Changelog for Project "Acute"

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.0.4] 2018-03-19

### Fixed

- check-example-project failed with changing version. Now removing
  version number from output before cparing with reference.

## [0.0.2] 2018-03-18

### Added

- Initial Release
- acute/testsuite.h: Implement test suites as programs.
- TAP format reporting
- EXPECT: EXPECT( a<b ), EXPECT( int, EQ(x*y,x*x) ), the 2-argument form with limited reporting
  of operand values on failure.
- EXPECT_UNEXPECTED, TEST_OK, TEST_FAIL.
- Isolation of tests in sub processes.
- Manual: Quick Start Guide
