bin=./flark
output=image.ppm
viewer=$(which feh)

# generate makefile
cmake . 

# build
make

# generate output image
rm $output
$bin >> $output

#display image
$viewer $output
