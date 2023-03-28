/*
------------------------------------------------------------------
Chat Server based on Socket.io
Eric Hobson

Static server implemented using 'node.js' and internal modules
------------------------------------------------------------------
`npm install`
`npm start`

To Test:
Open several browsers to: http://localhost:{PORT}/chatClient.html
------------------------------------------------------------------
*/

const server = require('http').createServer(handler)
const io = require('socket.io')(server)
const fs = require('fs')
const url = require('url');
const PORT = process.argv[2] || process.env.PORT || 3000

const ROOT_DIR = 'html'

const MIME_TYPES = {
    'css': 'text/css',
    'gif': 'image/gif',
    'htm': 'text/html',
    'html': 'text/html',
    'ico': 'image/x-icon',
    'jpeg': 'image/jpeg',
    'jpg': 'image/jpeg',
    'js': 'application/javascript',
    'json': 'application/json',
    'png': 'image/png',
    'svg': 'image/svg+xml',
    'txt': 'text/plain'
}

function get_mime(filename) {
    for (let ext in MIME_TYPES) {
        if (filename.indexOf(ext, filename.length - ext.length) !== -1) {
            return MIME_TYPES[ext]
        }
    }
    return MIME_TYPES['txt']
}

server.listen(PORT)

function handler(request, response) {
    let urlObj = url.parse(request.url, true, false)
    console.log('\n============================')
    console.log("PATHNAME: " + urlObj.pathname)
    console.log("REQUEST: " + ROOT_DIR + urlObj.pathname)
    console.log("METHOD: " + request.method)

    let filePath = ROOT_DIR + urlObj.pathname
    if (urlObj.pathname === '/') filePath = ROOT_DIR + '/index.html'

    fs.readFile(filePath, function (err, data) {
        if (err) {
            console.log('ERROR: ' + JSON.stringify(err))
            response.writeHead(404);
            response.end(JSON.stringify(err))
            return
        }
        response.writeHead(200, {
            'Content-Type': get_mime(filePath)
        })
        response.end(data)
    })

}

// object for storing the connected sockets
const connectedSockets = {}

// socket.io implementation
io.on('connection', function (socket) {
    console.log('client connected')
    socket.emit('connectedUsers', connectedSockets)

    // handle connecting to the chat room
    socket.on('clientID', function (data) {
        console.log('RECEIVED: ' + data)

        // create a room for the connected sockets
        socket.join("Chat Room")

        // stored the socket id with corresponding username
        connectedSockets[socket.id] = data
        console.log("connectedSockets: ", connectedSockets)

        // return acknowledgement that user successfully connected
        socket.emit('serverWelcome', `Welcome <b>${data}</b>, you are connected to "Chat Room"`)
        io.emit('connectedUsers', connectedSockets)
    })

    // handle public messages sent to chat room
    socket.on('clientSays', function (data) {
        console.log('RECEIVED: ', data)

        // used to gather information needed by client
        let returnMessage = {}

        /*
            id: handling client CSS
            user: username that sent message
            data: message contents
        */
        returnMessage.id = 'received'
        returnMessage.user = connectedSockets[socket.id]
        returnMessage.data = data.message

        // send to chat room, but not client that sent message
        socket.to("Chat Room").emit('serverSays', returnMessage);

        // adjust CSS and send to client that sent message
        returnMessage.id = 'sent'
        socket.emit('serverSays', returnMessage)
    })

    // handle private messages sent to chat room
    socket.on('clientSaysPrivately', function (data) {
        console.log('RECEIVED: ', data)

        // users to receive the private message
        let users = data.users
        let message = data.message

        // iterate through the users
        for (let i = 0; i < users.length; i++) {
            let user = users[i]

            // iterate through connectedSockets
            for (let id in connectedSockets) {

                // if the username matches the requested user
                if (connectedSockets[id] === user) {
                    let returnMessage = {}

                    returnMessage.user = connectedSockets[socket.id]
                    returnMessage.id = 'privateReceived'
                    returnMessage.data = message

                    io.to(id).emit('serverSays', returnMessage)
                }
            }
        }
        let returnMessage = {}

        returnMessage.user = connectedSockets[socket.id]
        returnMessage.id = 'privateSent'
        returnMessage.data = message

        socket.emit('serverSays', returnMessage)
    })

    socket.on('disconnect', function (data) {
        //event emitted when a client disconnects
        console.log('client disconnected')
        delete connectedSockets[socket.id]

        io.emit('connectedUsers', connectedSockets)
    })
})

console.log(`------------------------------------------------------------------`)
console.log(`Chat Server based on Socket.io`)
console.log(`Eric Hobson`)
console.log()
console.log(`Static server implemented using 'node.js' and internal modules`)
console.log(`------------------------------------------------------------------`)
console.log(`[Node.js] Server Running at port ${PORT}  CNTL-C to quit`)
console.log(`To Test:`)
console.log(`Open several browsers to: http://localhost:${PORT}/chatClient.html`)
