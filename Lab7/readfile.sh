#! /usr/bin/bash

while read -r field1 field2
do
       	mkdir -pv $field1
	touch $field1/$field2
done <"classes"
