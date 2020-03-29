let stream = require('./stream')

let opsys = process.platform;

let SSA = class {}

if (opsys == "darwin" || opsys == "linux") {
    SSA = require('./SilkroadSecurityJS.unix.node').SilkroadSecurityJS
} else if (opsys == "win32" || opsys == "win64") {
    SSA = require('./SilkroadSecurityJS.win.node').SilkroadSecurityJS
}

class SilkroadSecurityJS extends SSA {
    constructor(identity_name = "SR_Client", identity_flag = 0) {
        super(identity_name, identity_flag)
    }

    GenerateHandshake(blowfish = true, security_bytes = true, handshake = true) {
        return super.GenerateHandshake(blowfish, security_bytes, handshake)
    }

    ChangeIdentity(identity_name, identity_flag) {
        return super.ChangeIdentity(identity_name, identity_flag)
    }

    Recv(data = []) {

        if (data instanceof  Array) {
            return super.Recv(data)
        } else if (data instanceof Buffer) {
            
            return super.Recv(data.toJSON().data)
        }
        
    }

    GetPacketToRecv() {
        return (super.GetPacketToRecv() || [])
    }

    GetPacketToSend() {
        return (super.GetPacketToSend() || [])
    }

    Send(opcode = 0x0000, data = [], encrypted = false, massive = false) {

        let ndata = data

        if (data instanceof Buffer) {
            ndata = data.toJSON().data
        } else if (data instanceof stream.stream) {
            ndata = data.toData()
        }

        return super.Send(opcode, ndata, encrypted, massive)
    }

}

module.exports = {
    SilkroadSecurityJS: SilkroadSecurityJS,
    stream: {
        reader: stream.reader,
        writer: stream.writer
    }
}