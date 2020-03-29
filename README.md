# Silkroad Security JS 

This project is a Drew's SilkroadSecurity API wrapper to be use in node.js. 

## Installation

This security system is crossplatform, you can use it on unix (linux, macos (darwin)) system and win32/win64.

```bash
npm install silkroad-security --ignore-scripts
```

You can also install without ignoring scripts (it'll compile library during the installation, then you'll need to do the requirements step for compiling).

Install without ignoring scripts:

```bash
npm install silkroad-security
```

## Requirements

```bash
"node": ">=12.0.0"
```

## Installation

This security system is crossplatform, you can use it on unix (linux, macos (darwin)) system and win32/win64.

```bash
npm install silkroad-security --save
```

## Usage

```
const { SilkroadSecurityJS, stream } = require('silkroad-security-js')

let security = new SilkroadSecurityJS("SR_Client", 0)

security.GenerateHandshake(blowfish = true, security_bytes = true, handshake = true)
security.ChangeIdentity(identity_name = "SR_Client", identity_flag = 0)
security.Recv(data = [])
security.Send(opcode = 0x0000, data = [], encrypted = false, massive = false)
security.GetPacketToRecv() // return [{ opcode, data, encrypted, massive }]
security.GetPacketToSend() // return [{ opcode, data, encrypted, massive }]
```

## Examples

[clientless.js](https://github.com/EmirAzaiez/SilkroadSecurityJS/blob/master/examples/clientless.js) in this project you can see how Silkroad Security JS is working, you've to change IP, Port, version and local to make it working. This project will show you Silkroad Server status and capacity, you can also change it for join the game world.

## Compiling

### Requirements
Boost :
* linux : apt-get install libboost-dev 
* macos : brew install boost
* windows : [Get boost for windows](https://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html)

### Usage
```
npm install
node-gyp configure
node-build
```

Then you'll find all **.node** file in build *folder*

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Credits
Drew (pushedx)
Weeman

## License
[MIT](https://choosealicense.com/licenses/mit/)