const { URL } = require("url");// Not used yet.
const fse = require("fs-extra"); // v 5.0.0// Not used yet.
const path = require("path");// Not used yet.
// Create an instance of our puppeteer object.
const puppeteer = require("puppeteer");
/*
**  source: https://raw.githubusercontent.com/PokeMiners/game_masters/master/latest/latest.json
*/
const mon = require("./text.json");// Not used yet.
const poke = require("./test.json");// Not used yet.
// Create an instance of our pokemon data sheet object.
/*
**  source: https://raw.githubusercontent.com/PokeMiners/game_masters/master/latest/latest.json
*/
const moves = require("./moves.json");

// 
var browser;
var page;

// Create and define an instance object of the chrome options used for a puppeteer browser instance.
const chromeOptions = {
  // When headless is true the chrome browser instance will be a headless instance meaning there will be no physical chrome browser for users to interact with. This should boost performance.
  headless: false,
  defaultViewport: null,
};//end definition of chrome options object.
// Create an instance of our file system object.
var fs = require("fs");

// getScreen() scrapes the pvpoke page for the desired information. It stores the desired in a string type variable output and appends it to the outputfile of the appropriate thread which gets passed to the program as global arg-6.
async function getScreen(apatch){
  // The following instructions scrape a webpage for a set of data that is stored into a variable titled outputi where 0<i<5, or for each data variable to record. Await is used here so the all variables can be defined regardless of the status of the other variable since some results may load without others. This ensures we never get stuck waiting for a result that may not appear.
  var output1 = await page.evaluate(function() {
    let gnome = document.getElementsByClassName("grade")[0].innerHTML;
    gnome = document.getElementsByClassName("grade")[0].innerHTML;
    return gnome;
  });
  var output2 = await page.evaluate(function() {
    let gnome = document.getElementsByClassName("grade")[1].innerHTML;
    gnome = document.getElementsByClassName("grade")[1].innerHTML;
    return gnome;
  });
  var output3 = await page.evaluate(function() {
    let gnome = document.getElementsByClassName("grade")[2].innerHTML;
    gnome = document.getElementsByClassName("grade")[2].innerHTML;
    return gnome;
  });
  var output4 = await page.evaluate(function() {
    let gnome = document.getElementsByClassName("grade")[3].innerHTML;
    gnome = document.getElementsByClassName("grade")[3].innerHTML;
    return gnome;
  });
  page.close();
  //end collecting results.
  // Put outputs together i a string that makes sense and append to appropriate output file.
  var output = output1+output2+output3+output4+" " + apatch + " " + "\n";
  // Get output file and open it. If you can fileio better than I can please contribute to here.
  let file_name = "Output/pokemonOutput"+process.argv[5].toString()+".txt";
  let pokemonOutput = fs.open(file_name,'a', (err, fd) => {console.log("FileOpened" + fd);});
  fs.appendFileSync(file_name, output);
  fs.close(3);
  //end appending to appropriate file.
}//end getScreen()

// setSetTimeout() is an asynchronour timeout function. Its purpose is to alow the browser 3 seconds to render the pvpoke results so the js engine there has time to provide results for the set of pokemon we are running tests on.
async function setSetTimeout(apass) {
  // Set starting time.
  const start = Date.now();
  // Set current time.
  var now = Date.now();
  // The while() keeps track of time and ensures we do not exit the function before time is up.
  while ( now - start < 3000 ){
    now = Date.now();
  }
  // At this point in the function 3 seconds have passed and we are ready to create a call to the getScreen() function to collect data. The argument apass is the set of pokemon we are running the test on including their move #s. Presently I believe it is the actual pvpoke address.
  await getScreen(apass);
  return 1;
}//end setSetTimeout().


(async function main() {
  // Initialize an instance of a puppeteer web browser.
  browser = await puppeteer.launch(chromeOptions);
  // Initialize an instance of a new page in a puppeteer web browser.
  page = await browser.newPage();
/**   A JavaScript engine to simulate pokemon battles 
 *    Copyright 2021 PvPoke LLC
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, 
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
* is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or 
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/
  // the variable aTest stores the endpoint the tool uses to access the open source JS engine for pokemon battles. Currently it is using the live endpoint hosted by PvPoke LLC but can be cloned and implemented locally. Commented out is what a local host address may look like when ran using the XAMPP stack.
  var aTest = "https://pvpoke.com/team-builder/"; //"http://localhost/mypvpoke/src/team-builder/";// "https://pvpoke.com/team-builder/"; //
  var aMod = "";
  // Pokemon moves starting points are set here. Fast moves are set to  start from 0 because that is the all inclusive starting point in the JS engine. Charge moves need to start at 1 because 0 is the index for none and there is no reason for us to start with none for charge moves.
  var p1fMove = 0, p1cMove1 = 1, p1cMove2 = 2, p2fMove = 0, p2cMove1 = 1, p2cMove2 = 2, p3fMove = 0, p3cMove1 = 1, p3cMove2 = 2;
  //need to increment charge move maxs b/c charge moves index begins at 1, before one we find a none

  // The if() checks if the program has been passed a LARGE list or a SMALL list. If the conditional is true then the instructions for a LARGE list are carried out.
  if(!(process.argv[4].includes("-"))) {
    // The below instruction sets the MAX value a pokemons move can have. First the fast move MAX is set for each pokemon then the charge move MAX is set for each pokemon.
    let p1fMoveMAX = moves[process.argv[2].toLowerCase()][0]["quickMove"], p2fMoveMAX = moves[process.argv[3].toLowerCase()][0]["quickMove"], p3fMoveMAX = moves[process.argv[4].toLowerCase()][0]["quickMove"], p1cMoveMAX = moves[process.argv[2].toLowerCase()][0]["chargeMove"] + 1, p2cMoveMAX = moves[process.argv[3].toLowerCase()][0]["chargeMove"] + 1, p3cMoveMAX = moves[process.argv[4].toLowerCase()][0]["chargeMove"] + 1;
    
    for (var i = 0; i < 1; i++) {
      while ( p1fMove != p1fMoveMAX ) {
        page = await browser.newPage();// Whoops. IDK if this line is important. It will be left here for now until an assessment is completed.
        // aMod variable is a modifier to the aTest endpoint. When it gets appended to aTest is directs the browser page to the endpoint with the correct battle league the correct CP range and a complete set of pokemon with moves.
        aMod = "holiday/1500/"+process.argv[2].toLowerCase() + "-m-"+p1fMove+"-"+p1cMove1+"-"+p1cMove2+"%2C" + process.argv[3].toLowerCase()+ "-m-"+p2fMove+"-"+p2cMove1+"-"+p2cMove2+"%2C"  + process.argv[4].toLowerCase() + "-m-"+p3fMove+"-"+p3cMove1+"-"+p3cMove2 ;
        // Direct page to the correct address endpoint.
        await page.goto(aTest+aMod);
        await setSetTimeout(aMod);
        if ( p3cMove2 + 1 < p3cMoveMAX ) {
          p3cMove2 += 1;
        }
        else if ( p3cMove1 + 2 < p3cMoveMAX ) {
          p3cMove1 += 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else if ( p3fMove + 1 < p3fMoveMAX ) {
          p3fMove += 1;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else if ( p2cMove2 + 1 < p2cMoveMAX ) {
          p2cMove2 += 1;
          p3fMove = 0;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else if ( p2cMove1 + 2 < p2cMoveMAX ) {
          p2cMove1 += 1;
          p2cMove2 = p2cMove1 + 1;
          p3fMove = 0;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else if ( p2fMove + 1 < p2fMoveMAX ) {
          p2fMove += 1;
          p2cMove1 = 1;
          p2cMove2 = p2cMove1 + 1;
          p3fMove = 0;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else if ( p1cMove2 + 1 < p1cMoveMAX ) {
          p1cMove2 += 1;
          p2fMove = 0;
          p2cMove1 = 1;
          p2cMove2 = p2cMove1 + 1;
          p3fMove = 0;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else if ( p1cMove1 + 2 < p1cMoveMAX ) {
          p1cMove1 += 1;
          p1cMove2 = p1cMove1 + 1;
          p2fMove = 0;
          p2cMove1 = 1;
          p2cMove2 = p2cMove1 + 1;
          p3fMove = 0;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
        else {
          p1fMove += 1;
          p1cMove1 = 1;
          p1cMove2 = p1cMove1 + 1;
          p2fMove = 0;
          p2cMove1 = 1;
          p2cMove2 = p2cMove1 + 1;
          p3fMove = 0;
          p3cMove1 = 1;
          p3cMove2 = p3cMove1 + 1;
        }
      }
    }
  }//end if() LARGE list.
  // When the if() conditional is false then the instructions for a SMALL list gets ran below.
  else {
    page = await browser.newPage();
    aMod = process.argv[2];
    aTest += aMod;
    await page.goto(aTest);
    try{
      await setSetTimeout(aMod);
    } catch (e) {
      console.log(e);
    }
    console.log(aMod);
  }//end else SMALL list.
  process.exit();
})();
