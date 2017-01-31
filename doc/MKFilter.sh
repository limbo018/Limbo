##
# @file   MKFilter.sh
# @author Yibo Lin
# @date   Jan 2017
#
#!/bin/bash

echo !!!!!!!!!!!!!!!!!!!! $1 !!!!!!!!!!!!!!!!!!!!!
sed -e 's|##|//!|' $1
