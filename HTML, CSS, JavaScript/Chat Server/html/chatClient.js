// initialize socket connection
const socket = io()

// used for verifying username input against illegal characters
const format = /[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]+/

// flag to manage access if HTML edited directly from browser
let connected = false

// object used to keep track of users in chat room
let connectedUsers = {}

// socket event to update connectedUsers
socket.on('connectedUsers', function (data) {
    console.log("[connectedUsers] RECEIVED: ", data)
    connectedUsers = data
})

// socket event to acknowledge client successfully connected as user
socket.on('serverWelcome', function (message) {
    console.log("[serverWelcome] RECEIVED: ", message)

    // create new div with acknowledgement and append to welcome
    let msgDiv = document.createElement('div')
    msgDiv.innerHTML = message
    document.getElementById('welcome').appendChild(msgDiv)
})

// socket event to display messages in chat room
socket.on('serverSays', function (message) {
    console.log("[serverSays] RECEIVED: ", message)

    // creates and new div and sets corresponding id (for CSS)
    let msgDiv = document.createElement('div')
    msgDiv.setAttribute('id', message.id)

    // innerHTML formatting to better see who sent message
    msgDiv.innerHTML = `<font size="-0.75">${message.user}:</font>` + '<br>' + message.data

    // new div appended to messages
    document.getElementById('messages').appendChild(msgDiv)
})

// function to clear messages in client browser
function clearScreen() {
    document.getElementById('messages').innerHTML = ''
}

// function to present alert when called
function alertMessage(data) {
    alert(data)
}

// function to attempt connecting to chat room
function connectToServer() {
    // get the value from the username box
    let message = document.getElementById('idBox').value.trim()

    // reset to empty
    document.getElementById('idBox').value = ''

    // multiple checks regarding the username validity
    if (message === '') return // just exit if username field empty

    // test whether username contains illegal characters
    if (format.test(message)) {
        // post alert
        alertMessage("Username cannot contain special characters")
        return
    }

    // test whether username contains spaces
    if ((/\s/).test(message)) {
        // post alert
        alertMessage("Username cannot contain spaces")
        return
    }

    // check whether first character is a number
    if (!isNaN(message.charAt(0))) {
        // post alert
        alertMessage("Username cannot start with a number")
        return
    }

    // check whether username in use
    if (Object.values(connectedUsers).indexOf(message) > -1) {
        // post alert
        alertMessage("Username already exists")
        return
    }

    // all tests passed, hide id and show chat
    document.getElementById('id').hidden = true
    document.getElementById('chat').hidden = false

    // allows for connection
    connected = true

    // emit username to server
    console.log("[clientID] USERNAME SENT: ", message)
    socket.emit('clientID', message)
}

// funtion used to submit message to chat room
function sendMessage() {
    // get the message from the chat box
    let message = document.getElementById('msgBox').value.trim()

    // exit if message empty
    if (message === '') return

    // exits if not connected
    if (!connected) return

    // build object to submit to server
    let submissionData = {}

    // if ':' in message, always assumed text before first ':' is user/s
    const [start, ...end] = message.split(':')

    // rejoin message with rest of ':'. used to handle multiple ':'
    const privateMessage = end.join(':')

    // check whether ':' was used, if not, skip
    if (start !== message) {
        // formats users to remove spaces and only return usernames
        const usersWithoutSpaces = start.replaceAll(' ', '')

        // splits the users based on ','
        const privateUsers = usersWithoutSpaces.split(',')

        // set the message to send
        submissionData.message = privateMessage

        // array to send to server of the users who will receive message
        usersThatExist = []

        // iterate through requested users and check if connected
        for (user of privateUsers) {
            if (Object.values(connectedUsers).indexOf(user) > -1) {
                // if so add to submission array
                usersThatExist.push(user)
            }
        }

        // if at least 1 user exists, submit to server
        if (usersThatExist.length > 0) {
            console.log("[clientSaysPrivately] Users found: ", usersThatExist)
            submissionData.users = usersThatExist
            console.log("[clientSaysPrivately] PRIVATE SENT: ", submissionData)
            socket.emit('clientSaysPrivately', submissionData)
        } else {
            /*
                Message is not sent to the server unless at least 1 
                user from the private message exists. This allows
                for not sending unnecessary messages to the server.
            */
            alertMessage("No users match request")
        }

    } else {
        // if message does not contain ':', submitted to server normally
        submissionData.message = message
        console.log("clientSaysPrivately] PUBLIC SENT: ", submissionData)
        socket.emit('clientSays', submissionData)
    }

    // clears the chat box
    document.getElementById('msgBox').value = ''
}

// function for handling the enter key
function handleKeyDown(event) {
    //keycode for enter key
    const ENTER_KEY = 13

    if (event.keyCode === ENTER_KEY) {
        // works on both the username and chat field
        if (document.getElementById('chat').hidden) {
            connectToServer()
        } else {
            sendMessage()
        }
        return false
    }
}

// Add event listeners
document.addEventListener('DOMContentLoaded', function () {
    //This function is called after the browser has loaded the web page

    // add listener to buttons
    document.getElementById('send_button').addEventListener('click', sendMessage)
    document.getElementById('connect_button').addEventListener('click', connectToServer)
    document.getElementById('clear_button').addEventListener('click', clearScreen)

    //add keyboard handler for the document as a whole, not separate elements.
    document.addEventListener('keydown', handleKeyDown)
})
