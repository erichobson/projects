/*
Eric Hobson
buttonAndKeyListeners.js

JavaScript functions for handling button presses and 'enter' key press
*/

//KEY CODES
const ENTER = 13

// function used for handling 'enter' key press
function handleKeyUp(e) {
    if (e.which == ENTER) {
        getPuzzle() //treat ENTER key like you would a submit
        document.getElementById('userTextField').value = ''
    }

    e.stopPropagation()
    e.preventDefault()

}


// function for requesting a puzzle from the server
function getPuzzle() {

    // get value entered by user
    let userText = document.getElementById('userTextField').value

    if (userText && userText != '') {

        let textDiv = document.getElementById("text-area")

        // clear text-area
        textDiv.innerHTML = '';

        // print entered user data (puzzle name)
        textDiv.innerHTML = textDiv.innerHTML + `<p> ${userText}</p>`

        // build request object
        let userRequestObj = {
            text: userText
        }

        // clear used text field
        document.getElementById('userTextField').value = ''

        // fetch request for puzzle using POST
        fetch('/userText', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json', },
            body: JSON.stringify(userRequestObj),
        })
            .then((response) => response.json())
            .then((data) => {
                console.log('Success:', data)

                // clear words on canvas after every 'get puzzle'
                words = []

                // if there are puzzleLines, process and add to words
                let responseObj = data
                if (responseObj.puzzleLines) {

                    // iterate through puzzleLines, set each word in words
                    for (line of responseObj.puzzleLines) {
                        let word = {
                            word: line
                        }

                        // assign random locations for word and add to words
                        assignRandomIntCoords(word, canvas.width, canvas.height)
                        words.push(word)
                    }
                }
                drawCanvas()
            })
            .catch((error) => {
                console.error('Error:', error)
            })
    }
}


// function used to request solve response
function solvePuzzle() {

    // check if words on canvas, if not, return
    if (words.length === 0) return

    // checks canvas for word locations and aligns vertically
    locateWords()

    // save each word from words into solution array
    // used to send just the user solution to server
    var solution = []
    for (item of words) {
        solution.push(item.word)
    }

    // build request object
    let userRequestObj = {
        text: solution
    }

    // fetch request using POST to ask server for solution
    fetch('/solution', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json', },
        body: JSON.stringify(userRequestObj),
    })
        .then((response) => response.json())
        .then((data) => {
            console.log('Success:', data)

            // returns id to determine proper CSS
            let responseObj = data.text

            let textDiv = document.getElementById("text-area")
            textDiv.innerHTML = '';

            // initialize print string to build each line of solution
            let print = ''
            for (let i = 0; i < words.length; i++) {

                // final word handling, finish print and add to HTML with CSS id
                if (i == words.length - 1) {
                    print += words[i].word
                    textDiv.innerHTML = textDiv.innerHTML + `<span class=${responseObj}><p> ${print}</p></span>`
                    print = ''
                }

                // check whether next word has same y coordinate
                else if (words[i].y == words[i + 1].y) {
                    print += words[i].word + ' '
                }

                // final word of y coordinate, finish print and add to HTML with CSS id
                else {
                    print += words[i].word
                    textDiv.innerHTML = textDiv.innerHTML + `<span class=${responseObj}><p> ${print}</p></span>`
                    print = ''
                }
            }
        })
        .catch((error) => {
            console.error('Error:', error)
        })
}
