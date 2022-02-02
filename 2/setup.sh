chmod u+x six-degrees-*
chmod u+x zip.sh
wget https://github.com/freeuni-paradigms/assn-2-six-degrees-data/archive/master.zip
unzip master.zip
mv assn-2-six-degrees-data-master/data data
rm -r assn-2-six-degrees-data-master
rm master.zip
