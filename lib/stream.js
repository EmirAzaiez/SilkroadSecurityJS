class stream {
    constructor() {}
}
class writer extends stream {

    constructor() {
        super()
        this.buffer = Buffer.alloc(4096);
        this.pointer = 0;
        this.size = 0;
    }

    uint8(b) {

        this.buffer.writeUInt8(b, this.pointer);

        if(this.pointer == this.size) {
            this.pointer += 1;
            this.size += 1;
        } else {
            this.pointer += 1;
        }

    }

    uint16(b) {

        this.buffer.writeUInt16LE(b, this.pointer);

        if(this.pointer == this.size) {
            this.pointer += 2;
            this.size += 2;
        } else {
            this.pointer += 2;
        }

    }

    uint32(b) {

        this.buffer.writeUInt32LE(b, this.pointer);

        if(this.pointer == this.size) {
            this.pointer += 4;
            this.size += 4;
        } else {
            this.pointer += 4;
        }

    }

    float(b) {

        this.buffer.writeFloatLE(b, this.pointer);

        if(this.pointer == this.size) {
            this.pointer += 4;
            this.size += 4;
        } else {
            this.pointer += 4;
        }

    }

    string(str) {

        var vstr = new String(str);
        var len = vstr.length; 
        this.uint16(len);
        this.buffer.write(str, this.pointer);
        
        if(this.pointer == this.size) {
            this.pointer += len;
            this.size += len;
        } else {
            this.pointer += len;
        }

    }

    toData() {
        return this.buffer.slice(0, this.size).toJSON().data
    }
   
}

class reader extends stream {

    constructor(data) {
        super()
        this.buffer = Buffer.from(data)
        this.pointer = 0;
    }

    uint8() {
		var value = this.buffer.readUInt8(this.pointer);
		this.pointer++;
		return value;
    }
    
	uint16() {

		var value = this.buffer.readUInt16LE(this.pointer);
		this.pointer += 2;
		return value;
    }
     
	uint32() {
		var value = this.buffer.readUInt32LE(this.pointer);
		this.pointer += 4;
		return value;
    }

    uint64() {
        var value = this.buffer.readUIntLE(this.pointer, 8)
        // var value = this.buffer.readBigUInt64LE(this.pointer);
		this.pointer += 8;
		return value;
    }
    
	string() {
        var len = this.uint16();
        var str = this.buffer.toString("utf8", this.pointer, this.pointer + len);
        this.pointer += len;
        return str;
    }
    
	float() {
	    var value = this.buffer.readFloatLE(this.pointer);
	    this.pointer += 4;
	    return value;
    }
    
	bool()
	{
	    if (this.buffer.readUInt8(this.pointer) == 1) {
	        return true;
	    } else {
	        return false;
        }
        
    }

    toData() {
        return this.buffer.toJSON().data
    }
    
}

module.exports = {
    writer: writer,
    reader: reader,
    stream: stream
}