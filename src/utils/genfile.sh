for i in $(seq 1 30)
do 
  size=$((4096*100*i))
  path="/media/cthye/Cthye/221-prime"
  ./gensort $path/$size $size
done