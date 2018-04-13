rm -f ../Eigen.tar.gz
wget https://www.dl.dropboxusercontent.com/s/hhynuknplh3gwgp/Eigen.tar.gz -P ../include/
rm -rf ../Eigen
mkdir ../include/eigen3/
tar xzf ../include/Eigen.tar.gz -C ../include/eigen3/
rm -f ../include/Eigen.tar.gz

