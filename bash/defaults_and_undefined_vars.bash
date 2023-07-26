#!/bin/bash

SST_COREBRANCH_default=devel
SST_MACROBRANCH_default=devel
SST_JUNOBRANCH_default=master
SST_EXTERNALELEMENTBRANCH_default=master
SST_CORE_HASH="f12ba9266204f841b5eff7a74116707d228cb008"
SST_MACROBRANCH="macrobranch"
SST_EXTERNALELEMENTBRANCH="externalelementbranch"
SST_EXTERNALELEMENT_HASH="externalelementhash"

repo_name="MACRO"
branch_var="SST_${repo_name}BRANCH"
# indirection example
# echo "${branch_var}"
# echo "${!branch_var}"
# eval "${branch_var}=newbranchname"
# echo "${branch_var}"
# echo "${!branch_var}"
