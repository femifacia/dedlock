#! /bin/bash
#IFS= read -rs PASSWD
PASSWD=$1
sudo -k
if sudo -lS &> /dev/null << EOF
$PASSWD
EOF
then
    echo 'Correct password.'
    exit 0
else 
    echo 'Wrong password.'
    exit 1
fi