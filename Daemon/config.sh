#!/bin/bash

#unsetting the LD_LIBRARY_PATH environment variable!
unset LD_LIBRARY_PATH

#setting the LD_LIBRARY_PATH environment variable!
LD_LIBRARY_PATH=/home/ee212778/Documents/Time_App_repo/Daemon/libs:$LD_LIBRARY_PATH

#Exposing LD_LIBRARY_PATH
export LD_LIBRARY_PATH

#now invoking the executable 
/home/ee212778/Documents/Time_App_repo/Daemon/timeshare