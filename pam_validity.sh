#!/bin/bash

VAR1=$(/usr/bin/python3 <<EOF
from prototype import *
open9x()
identify()
exit()
EOF
)


if [[ $VAR1 == *finger* ]]
then
#   echo "Success!"
   exit 0
else
#   echo "Failure!"
   exit 114
fi

#echo "${VAR1}"
