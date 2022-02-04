:: Script called by CMake to install development
:: tools such as pre-commit, w/e

:: TODO install python if not available

REM Installing development tools
REM Installing and configuring pre-commit
pip install pre-commit
pre-commit install
