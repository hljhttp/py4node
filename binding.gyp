{
  "targets": [{
    "target_name": "pblock",
    "defines" : ["NOMINMAX=1"],
    "include_dirs" : [
      "src",
      "<!(node -e \"require('nan')\")",
      "g:\ChatMs\Miniconda2\include",
      "g:\ChatMs\makecode\pybind11\include"      
    ],
    "libraries": [
      "g:/ChatMs/Miniconda2/libs/python27"
    ],
    "sources": [
      "src/index.cc",
      "src/PyBlock.cc"
    ]
  }]
}