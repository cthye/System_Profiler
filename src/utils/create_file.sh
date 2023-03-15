# example: 
# ./src/utils/create_file.sh ~/ucsd/nfs
echo "file dir path: $1";
for i in $(seq 1 30)
do
  dd bs=4096 count=$i if=/dev/urandom of=$1/$i
done
  