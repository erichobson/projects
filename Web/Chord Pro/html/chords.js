// Array of base chords with equivalent sharps and flats
const baseChordArray = [['A', 'A'], ['A#', 'Bb'], ['B', 'B'], ['C', 'C'], ['C#', 'Db'], ['D', 'D'], ['D#', 'Eb'], ['E', 'E'], ['F', 'F'], ['F#', 'Gb'], ['G', 'G'], ['G#', 'Ab']]

// used to globally store the song text without chords
let chordProLinesArrayNoChords = []

// used to globally store the current chords of song
let currentChords = []

// used to globally store the chords used about song (chords and spaces)
let chordArray = []

// used to keep track of original chord
let chordCount = 0


function parseChordProFormat(chordProLinesArray) {
    chordCount = 0
    chordProLinesArrayNoChords = []

    // store the chords temporarily to check for duplicates
    let tempChords = []
    currentChords = []

    // store the chord to remove from chordProLinesArray
    let chordToRemove = ""
    let chordsToRemove = []

    // store each individual chord
    let chordIndividual = ""
    // store the chord string
    let chordString = ""
    // check if character is part of chord
    let check = false

    console.log('type of input: ' + typeof chordProLinesArray)

    //add the lines of text to html <p> elements
    let textDiv = document.getElementById("text-area")
    textDiv.innerHTML = '' //clear the html

    // iterate through each line of chordProLinesArray and build chordString
    for (let line of chordProLinesArray) {
        // if line contains a chord
        if (line.includes("[")) {

            // count for length of the chord, used manage spaces in chordString
            let count = 0

            // iterate through characters of line
            for (let char of line) {
                // if character is start of chord
                if (char === "[") {
                    check = true

                    // add initial character to chordIndividual
                    chordIndividual += char
                    // add initial character to chordToRemove
                    chordToRemove += char

                    // check to see if previous character is not a space
                    // used to manage spaces in chordString
                    if (chordString[chordString.length - 1] !== " ") {
                        chordString += " "
                        count++
                    }
                } else if (char === "]") {
                    // add final character to chordIndividual
                    chordIndividual += char
                    // add final character to chordToRemove
                    chordToRemove += char

                    // add chordToRemove to chordsToRemove
                    if (!chordsToRemove.includes(chordToRemove)) {
                        chordsToRemove.push(chordToRemove)
                    }

                    // add chordIndividual to tempChords
                    if (!tempChords.includes(chordIndividual)) {
                        tempChords.push(chordIndividual)
                    }

                    // reset
                    chordToRemove = ""
                    chordIndividual = ""
                    check = false

                } else if (char === "/") {
                    // this section is to manage chords seperated by a slash

                    // character added to chordToRemove so we can take entire section out of song
                    chordToRemove += char

                    // add chordIndividual to tempChords
                    chordIndividual += "]"
                    if (!tempChords.includes(chordIndividual)) {
                        tempChords.push(chordIndividual)
                    }
                    chordIndividual = "["
                    // then reset and continue chordIndividual

                    chordString += char
                    count += 1

                } else if (check) {
                    // if character is part of chord

                    // add character to chordIndividual and chordToRemove
                    chordToRemove += char
                    chordIndividual += char

                    // add character to chordString
                    chordString += char
                    count += 1

                } else if (!check) {
                    // if character is not part of chord

                    // if count > 0, do not add space to chordString
                    if (count > 0) {
                        count--

                    } else { // add space to chordString
                        chordString += " "
                    }
                }
            }
            // end of line, add new line to chordString
            chordString += "\n"

        } else { // if line does not contain a chord
            chordString += "\n"
        }
    }

    // iterate through tempChords, remove unnecessary characters, and add to currentChords
    for (let chord of tempChords) {
        // remove brackets if chord length is 3
        if (chord.length === 3) {
            chord = chord.slice(1, 2)

        } else {
            // check if chord is a sharp or flat
            if (chord[2] === "#" || chord[2] === "b") {
                chord = chord.slice(1, 3)

            } else {
                // not sharp, flat, or bracket, remove exterior element
                chord = chord.slice(1, 2)
            }
        }

        // check if chord is already in currentChords
        if (currentChords.find(element => element[0] == chord)) { break }

        // check if chord is in baseChordArray
        for (let i = 0; i < baseChordArray.length; i++) {
            for (let j = 0; j < baseChordArray[i].length; j++) {
                if (chord === baseChordArray[i][j]) {
                    // add final chord to currentChords
                    currentChords.push([[baseChordArray[i][j]], [i, j]])
                    break
                }
            }
        }
    }

    // split chordString into chordArray
    chordArray = chordString.split("\n")

    // iterate through chordArray and replace chords with base chords
    for (let line in chordArray) {
        for (let chord of currentChords) {
            chordArray[line] = chordArray[line].replaceAll(baseChordArray[chord[1]], chord[0])
        }
    }

    // used to keep track of index of chordArray
    let index = 0

    // iterate through chordProLinesArray\
    for (let line of chordProLinesArray) {

        // remove chords from line
        for (let chord of chordsToRemove) {
            line = line.replaceAll(chord, "")
        }

        // add line to chordProLinesArrayNoChords
        chordProLinesArrayNoChords.push(line)

        // if line does not contain a chord (used to manage spacing)
        if (!chordArray[index].trim()) {
            textDiv.innerHTML = textDiv.innerHTML + `<pre> ${line}</pre>`
            console.log(line)

        } else { // print chord and line
            textDiv.innerHTML = textDiv.innerHTML + `<pre class="chord"> ${chordArray[index]}</pre>`
            textDiv.innerHTML = textDiv.innerHTML + `<pre> ${line}</pre>`
            console.log(chordArray[index])
            console.log(line)
        }
        index++
    }
}


// transpose chords up or down
function transpose(direction) {
    if (direction === "up") { // transpose up
        console.log("Transpose Up")
        chordCount++

        // iterate through currentChords
        for (let i = 0; i < currentChords.length; i++) {
            // check if currentChords is at end of baseChordArray
            if (currentChords[i][1][0] === baseChordArray.length - 1) {
                // reset to beginning of baseChordArray
                currentChords[i][1][0] = 0
            } else {
                currentChords[i][1][0] += 1
            }

            // randomly choose b or # if available
            let rand = Math.random()
            if (rand < 0.5) {
                rand = 0
            } else {
                rand = 1
            }
            currentChords[i][1][1] = rand
        }
    } else if (direction === "down") { // transpose down
        console.log("Transpose Down")
        chordCount--

        // iterate through currentChords
        for (let i = 0; i < currentChords.length; i++) {
            // check if currentChords is at beginning of baseChordArray
            if (currentChords[i][1][0] === 0) {
                // reset to end of baseChordArray
                currentChords[i][1][0] = baseChordArray.length - 1
            } else {
                currentChords[i][1][0] -= 1
            }

            // randomly choose b or # if available
            let rand = Math.random()
            if (rand < 0.5) {
                rand = 0
            } else {
                rand = 1
            }
            currentChords[i][1][1] = rand
        }
    }

    //add the lines of text to html <p> elements
    let textDiv = document.getElementById("text-area")
    textDiv.innerHTML = '' //clear the html

    // array to store new chordArray
    let transposeChordArray = []

    // iterate through chordArray and create replacement transposed chords
    for (let line of chordArray) {

        // tempLine used to build line to store in transposeChordArray
        let tempLine = ""

        // stores the chord to be replaces
        let chordFromLine = ""

        // iterate through each character in line
        for (let i = 0; i < line.length; i++) {

            // check if character is a space
            if (line[i] != " ") {

                // check if character is a chord
                if (line[i] === "A" || line[i] === "B" || line[i] === "C" || line[i] === "D" || line[i] === "E" || line[i] === "F" || line[i] === "G") {

                    // check if chord is a sharp or flat
                    if (line[i + 1] === "#" || line[i + 1] === "b") {
                        // add chord to chordFromLine with sharp or flat
                        chordFromLine = line[i] + line[i + 1]
                    } else {
                        // add chord to chordFromLine without sharp or flat
                        chordFromLine = line[i]
                    }

                    // iterate through currentChords to find chordFromLine
                    for (let chord of currentChords) {
                        if (chord[0] == chordFromLine) {
                            // store replacement chord in tempLine
                            replace = baseChordArray[chord[1][0]][chord[1][1]]
                            tempLine += replace
                            break
                        }
                    }

                } else if (line[i] === "#" || line[i] === "b") {
                    // skip because it is part of a chord and previously added
                    continue
                } else {
                    // add other character to tempLine
                    tempLine += line[i]
                }
            } else {
                // add space to tempLine
                tempLine += line[i]
            }
        }
        // add tempLine to transposeChordArray
        transposeChordArray.push(tempLine)
    }

    // replace chordArray with transposeChordArray
    chordArray = transposeChordArray
    // reset transposeChordArray
    transposeChordArray = []

    // iterate through currentChords and replace chord with new transposed chord
    for (let chord of currentChords) {
        chord[0] = baseChordArray[chord[1][0]][chord[1][1]]
    }

    // used to keep track of index of chordArray
    let index = 0

    // iterate through chordProLinesArrayNoChords
    for (let line of chordProLinesArrayNoChords) {

        // if line does not contain a chord (used to manage spacing)
        if (!chordArray[index].trim()) {
            textDiv.innerHTML = textDiv.innerHTML + `<pre> ${line}</pre>`
            console.log(line)

        } else { // print chord and line

            // if chordCount mod 12 is 0, print chord without transposition CSS
            if (chordCount % 12 == 0) {
                textDiv.innerHTML = textDiv.innerHTML + `<pre class="chord"> ${chordArray[index]}</pre>`
                textDiv.innerHTML = textDiv.innerHTML + `<pre> ${line}</pre>`
            } else { // print chord with transposition CSS
                textDiv.innerHTML = textDiv.innerHTML + `<pre class="chord-transposed"> ${chordArray[index]}</pre>`
                textDiv.innerHTML = textDiv.innerHTML + `<pre> ${line}</pre>`
            }
            console.log(chordArray[index])
            console.log(line)
        }
        index++
    }
}
