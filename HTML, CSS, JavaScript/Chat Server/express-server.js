/*
------------------------------------------------------------------
Chat Server based on Socket.io
Eric Hobson

express-server.js:
Static server implemented using 'Express' framework
------------------------------------------------------------------
`npm install`
`npm run express`

To Test:
Open several browsers to: http://localhost:{PORT}/chatClient.html
------------------------------------------------------------------
*/

// set requirements for express server
const express = require('express')
const app = express()
const http = require('http')
const server = http.createServer(app)
const { Server } = require("socket.io")
const io = new Server(server)

// get port or set to default
const PORT = process.env.PORT || 3000

// root directory for our static pages
const ROOT_DIR = '/html'

// handle requests
app.use(function (req, res, next) {
    console.log('-------------------------------')
    console.log('req.path: ', req.path)
    console.log('serving:' + __dirname + ROOT_DIR + req.path)
    next(); //allow next route or middleware to run
})

// provide the static server
app.use(express.static(__dirname + ROOT_DIR))

// handle invalid requests
app.use((req, res) => {
    res.status(404).send('404: INVALID REQUEST')
})

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

// start server
server.listen(PORT, err => {
    if (err) console.log(err)
    else {
        console.log(`------------------------------------------------------------------`)
        console.log(`Assignment 3: Chat Server based on Socket.io`)
        console.log(`Eric Hobson - 100826320`)
        console.log()
        console.log(`Static server implemented using 'Express' framework`)
        console.log(`------------------------------------------------------------------`)
        console.log(`[Express] Server listening on port: ${PORT} CNTL-C to Quit`)
        console.log(`To Test:`)
        console.log(`Open several browsers to: http://localhost:${PORT}/chatClient.html`)
    }
})