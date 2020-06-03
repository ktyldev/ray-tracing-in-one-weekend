bin=./flark
output=image.ppm
viewer=$(which feh)

if [ -f $bin ];
then
    echo "Removing old binary"
    rm $bin
fi

# generate makefile
cmake . 

# build
make

# generate output image
rm $output
$bin >> $output

#display image
$viewer $output
