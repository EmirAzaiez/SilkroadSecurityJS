const { SilkroadSecurityJS, stream } = require('silkroad-security'),
    net = require('net');

let silkroad = {
        ip: '127.0.0.1',
        port: 15779,
        version: 201,
        local: 22
    },
    security = new SilkroadSecurityJS(),
    client = new net.Socket()
    

client.connect({
    host: silkroad.ip,
    port: silkroad.port,
    onread: {
        buffer: Buffer.alloc(8 * 1024)
    }
});

client.on('data', (data) => {
    security.Recv(data.toJSON().data)
});

setInterval(() => {

    let packToSend = security.GetPacketToSend()

    for (let y = 0; y < packToSend.length; y++) {
        let data = Buffer.from(packToSend[y])
        client.write(data)
    }

    let packetToRecv = security.GetPacketToRecv()

    for (let i = 0; i < packetToRecv.length; i++) {
        HandlePacketGateway(security, packetToRecv[i])
    }


}, 1)

client.on('close', () => {
	console.log('Connection closed');
});

function HandlePacketGateway(security, packet) {

    let reader = new stream.reader(packet['data'])

    console.log((packet['opcode']).toString(16))

    if (packet['opcode'] == 0x2001) {

        let server = reader.string()

		if (server == 'GatewayServer') {

            let rep = new stream.writer();
            rep.uint8(silkroad.local);
            rep.string("SR_Client");
            rep.uint32(silkroad.version);
            
            security.Send(0x6100, rep.bytes().toJSON().data, true, false)

        } 
            
    } else if (packet['opcode'] == 0xA100) {

        security.Send(0x6101, [], true, false)

    } else if (packet['opcode'] == 0xA101) {

        while (reader.uint8() == 1) {
            reader.uint8();
            reader.string('ascii');
        }

        var servers = []

        while (reader.uint8() == 1) {
            var server = {
                serverID: reader.uint16(),
                Name: reader.string('ascii'),
                ratio : reader.float(),
                status: reader.uint8()
            };

            server.players = Math.round(server.ratio * 3500.0);
            servers.push(server);
        }

        console.log('--- Servers ---')
        console.log(servers);

    }

}