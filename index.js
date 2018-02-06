// this is how we will require our module
const m = require('../pblock')

const vec1 = new m.PyBlock("b1")
console.log(vec1) // Vector { x: 20, y: 10, z: 0 }




const vecSum = vec1.call("tttt","good",{"name":"binchen333dd"})
console.log(vecSum) // Vector { x: 50, y: 10, z: 100 }