/* 
Eric Hobson
eventListener.js

event listeners for buttons and key presses
*/

document.addEventListener('DOMContentLoaded', function () {
    document.getElementById('canvas1').addEventListener('mousedown', handleMouseDown)
    document.getElementById('get_puzzle').addEventListener('click', getPuzzle)
    document.getElementById('solve_puzzle').addEventListener('click', solvePuzzle)

    document.addEventListener('keyup', handleKeyUp)

    randomizeWordArrayLocations(words)

    drawCanvas()
})
