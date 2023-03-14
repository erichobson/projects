/*
Eric Hobson
canvas.js

JavaScript functions used for managing the canvas
*/


// Use javascript array of objects to represent words and their locations
let words = []

// drawing canvas
const canvas = document.getElementById('canvas1')


// function used to assign random location to words
function assignRandomIntCoords(object, maxX, maxY) {
    const MARGIN = 50 //keep way from edge of canvas by MARGIN
    object.x = MARGIN + Math.floor(Math.random() * (maxX - 2 * MARGIN))
    object.y = MARGIN + Math.floor(Math.random() * (maxY - MARGIN))
}


// function used to randomize the locations for words
function randomizeWordArrayLocations(wordsArray) {
    for (word of wordsArray) {
        assignRandomIntCoords(word, canvas.width, canvas.height)
    }
}


randomizeWordArrayLocations(words)
//====================================

// function to get word at mouse click location
function getWordAtLocation(aCanvasX, aCanvasY) {
    var context = canvas.getContext('2d')
    context.font = '20pt Arial'
    const TOLERANCE = 20
    for (var i = 0; i < words.length; i++) {
        var wordWidth = context.measureText(words[i].word).width
        if ((aCanvasX > words[i].x && aCanvasX < (words[i].x + wordWidth)) &&
            Math.abs(words[i].y - aCanvasY) < TOLERANCE) return words[i]
    }
    return null
}

// function to locate words in the canvas
function locateWords() {
    /*
    Split the canvas into 8 sections to build solution. I decided to 
    go this way because sorting the words based on x and y gave a 
    consistent result for words location. This does however lead to a 
    max puzzle size of 9 lines and set row locations in canvas (with
    appropriate space for the user to not have to be too specific).

    ~~~~~~~~~
    section 1
    ---------
    section 2
    ---------
       ...
    ---------
    section 9
    ~~~~~~~~~
    */

    // size of section is 1/9 of canvas height
    let section = canvas.height / 9

    // const used to center word in section
    const centerOffset = 26

    /* check location of y and use appropriate section 1-9.
       6 used as buffer since y location of word is bottom left corner, 
       this allows for a more consistent spacing for user selection */
    for (item of words) {
        if (item.y - 6 <= section) {
            item.y = centerOffset

        } else if (item.y + 6 > section && item.y - 6 <= section * 2) {
            item.y = section + centerOffset

        } else if (item.y + 6 > section * 2 && item.y - 6 <= section * 3) {
            item.y = section * 2 + centerOffset

        } else if (item.y + 6 > section * 3 && item.y - 6 <= section * 4) {
            item.y = section * 3 + centerOffset

        } else if (item.y + 6 > section * 4 && item.y - 6 <= section * 5) {
            item.y = section * 4 + centerOffset

        } else if (item.y + 6 > section * 5 && item.y - 6 <= section * 6) {
            item.y = section * 5 + centerOffset

        } else if (item.y + 6 > section * 6 && item.y - 6 <= section * 7) {
            item.y = section * 6 + centerOffset

        } else if (item.y + 6 > section * 7 && item.y - 6 <= section * 8) {
            item.y = section * 7 + centerOffset

        } else if ((item.y + 6 > section * 8 && item.y <= canvas.height) || item.y > canvas.height) {
            item.y = section * 8 + centerOffset
        }
    }

    // sort words based on x (horizontally)
    words.sort(
        (word1, word2) => (word1.x > word2.x) ? 1 : (word1.x < word2.x) ? -1 : 0)

    // sort words based on y (vertically)
    words.sort(
        (word1, word2) => (word1.y > word2.y) ? 1 : (word1.y < word2.y) ? -1 : 0)

    // re-draw the canvas
    drawCanvas()
}


// function used to draw the canvas
function drawCanvas() {

    const context = canvas.getContext('2d')
    context.fillStyle = 'rgb(255, 255, 255)'
    context.fillRect(0, 0, canvas.width, canvas.height)

    context.font = '20pt Arial'
    context.fillStyle = 'cornflowerblue'
    context.strokeStyle = 'blue'

    for (let i = 0; i < words.length; i++) {

        let data = words[i]
        context.fillText(data.word, data.x, data.y)
        context.strokeText(data.word, data.x, data.y)

    }
    context.stroke()
}
