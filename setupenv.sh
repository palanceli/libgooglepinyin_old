# # git submodule update --init --recursive
# git submodule add https://github.com/google/googletest.git modules/googletest
# cd modules/googletest
# git checkout release-1.8.0

# cd ../..
# git submodule add https://github.com/google/glog.git modules/glog
# cd modules/glog
# git checkout v0.3.5

# cd ../..
# git submodule add https://github.com/gflags/gflags.git modules/gflags
# cd modules/gflags
# git checkout v2.2.1

# cd modules/googletest
# mkdir _build
# cd _build
# cmake ..
# make 
# make install

# cd modules/gflags
# mkdir _build
# cd _build
# cmake ..
# make
# make install

# cd modules/glog
# mkdir _build
# cd _build
# cmake ..
# make
# make install