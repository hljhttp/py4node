var pblock

if (process.env.DEBUG) {
  pblock= require('./build/Debug/pblock.node')
} else {
  pblock= require('./build/Release/pblock.node')
}

module.exports = pblock