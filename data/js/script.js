/**
 * @author  Timo Schwarzer (timo.schwarzer@festo.com)
 */
// VARIABLES
// Variable zum speichern des aktiven Projektes
var activeProject = "bionic_fish";
var availableProjects = ["bionic_fish","bionic_elephant_trunk","bionic_chameleon_tongue"]; 

// Project IDs
var fishIds = ['fish-servo-1','fish-servo-2','fish-servo-3'];
var elephantIds = ['ele-servo-1','ele-servo-2','ele-servo-3', 'ele-servo-4'];
var chameleonIds = ['cha-servo-1'];

// The 4 values containing the data from the webServer for all projects
var valueIds = ['value01','value02','value03','value04'];

// JQUERY
$(document).ready(function () {

    console.log("Call READY");
    // NAVIGATION
    $('a[data-toggle="tab"]').click(function (event) {
        var paramStr = '' + event.target.id;
        activeProject = paramStr;
        switchProject(paramStr);
    });

    $(document).on('click','.navbar-collapse.in',function(e) {
        if( $(e.target).is('a') ) {
            $(this).collapse('hide');                   
        }
    });

    //console.log("Call update_page");

    // FISH   
    var fish_slider_1 = $('#fish-servo-1').slider({});
    var fish_slider_2 = $('#fish-servo-2').slider({});
    var fish_slider_3 = $('#fish-servo-3').slider({}); 

    // ELEPHANT
    var ele_slider_1 = $('#ele-servo-1').slider({});
    var ele_slider_2 = $('#ele-servo-2').slider({});
    var ele_slider_3 = $('#ele-servo-3').slider({}); 
    var ele_slider_4 = $('#ele-servo-4').slider({}); 

    ele_slider_1.val()

    // CHAMELEON
    var cha_slider_1 = $('#cha-servo-1').slider({});
     
   
    $('#fish .slider').bind('slideStop', function(e) {
        setWerteFish();
    });


    $('#elephant .slider').bind('slideStop', function(e) {
        setWerteElephant();
    });  


    $('#chameleon .slider').bind('slideStop', function(e) {
        setWerteChameleon();
    });  
    
    

    $('a[data-toggle="tab"]').on('shown.bs.tab', function(e) {                
    ele_slider_1.slider('refresh');
    ele_slider_2.slider('refresh');
    ele_slider_3.slider('refresh');
    ele_slider_4.slider('refresh');

    fish_slider_1.slider('refresh');
    fish_slider_2.slider('refresh');
    fish_slider_3.slider('refresh');

    cha_slider_1.slider('refresh');        
    });

    workerGetWerte();
    switchProject(activeProject);
    
});

function setWerteFish()
{       
    console.log("Call setWerteFish");
    setWerte($('#fish-servo-1').val(), 
             $('#fish-servo-2').val(), 
             $('#fish-servo-3').val()); 
    
}

function setWerteElephant()
{    
    console.log("Call setWerteElephant");
    setWerte($('#ele-servo-1').val(),
             $('#ele-servo-2').val(),
             $('#ele-servo-3').val(),
             $('#ele-servo-4').val());
    
}

function setWerteChameleon()
{
    console.log("Call setWerteChameleon");
    setWerte($('#cha-servo-1').val(),
             $('#cha-servo-1').val(),
             $('#cha-servo-1').val(),
             $('#cha-servo-1').val());
}

// AJAX POST CALL /setWerte
function setWerte(val1 = 0, val2 = 0, val3 = 0, val4 = 0) {
    console.log("Call setWerte");
    $.post("/setWerte",
        {
            value01: val1,
            value02: val2,
            value03: val3,
            value04: val4
        },
        function (data, status) {
            //console.log("Data: " + data + "\nStatus: " + status);
        });
}


// AJAX POST CALL /switchProject
function switchProject(paramStr) {    
    console.log("Call switchProject");
    $.post("/switchProject",
        {
            activeProject: paramStr
        },
        function (data, status) {
            //console.log("Data: " + data + "\nStatus: " + status);
            workerGetWerte();
            //update_page();
        }
        
    );
}


// RECURSIVE AJAX GET CALL /getWerte
function workerGetWerte() {    
    console.log("Call workerGetWerte");
    $.ajax({
        url: '/getWerte',
        success: function(data) {                
            writeAntwort(data);
            //update_page();
        },
        complete: function() {
            // Schedule the next request when this one has completed
            //setTimeout(workerGetWerte, 2000);            
        }
    })
}

function writeAntwort(str) 
{        
    console.log("Call writeAntwort: ");
    console.log(str)
    var element;
    var arr = str.split('&');
    for (var i=0; i<arr.length; i++)    
    {
        var keyVal = arr[i].split('=');
        
        switch (activeProject)
        {
            // Fish
            case availableProjects[0]:
                writeFishValues(keyVal);
                break;
            
            // Elephant trunk
            case availableProjects[1]:
                writeElephantValues(keyVal);
                break;

            // Chameleon tongue
            case availableProjects[2]:
                writeChameleonValues(keyVal);
                break;

            default:
                break;
        }
    }
}

function writeFishValues(keyVal)
{   
    //console.log("keyVal: " + keyVal);
    console.log("Call writeFishValues");
    //console.log("F1 Value: "+$("#fish-servo-1").slider('getValue'));
    //console.log("F2 Value: "+$("#fish-servo-2").slider('getValue'));
    //console.log("F3 Value: "+$("#fish-servo-3").slider('getValue'));
    
    switch (keyVal[0])
    {
        case valueIds[0]:            
            //document.getElementById(fishIds[0]).value = keyVal[1];
            //console.log("change F1 to: "+keyVal[1]);
            $('#fish-servo-1').slider('setValue', keyVal[1],true);            
            //console.log("F1 Value: "+$("#fish-servo-1").slider('getValue'));
            break;
        case valueIds[1]:
            //console.log("change F2 to: "+keyVal[1]);
            //document.getElementById(fishIds[1]).value = keyVal[1];
            $("#fish-servo-2").slider('setValue', keyVal[1],true);
            //console.log("F2 Value: "+$("#fish-servo-2").slider('getValue'));
            
            //$("#fish-servo-2").slider('refresh');
            break;
        case valueIds[2]:
            //console.log("change F3 to: "+keyVal[1]);
            //document.getElementById(fishIds[2]).value = keyVal[1];
            $("#fish-servo-3").slider('setValue', keyVal[1],true);
            //console.log("F3 Value: "+$("#fish-servo-3").slider('getValue'));
            //$("#fish-servo-3").slider('refresh');
            break;
        case valueIds[3]:
            //console.log("F1 Value: "+$("#fish-servo-1").slider('getValue'));
            //console.log("F2 Value: "+$("#fish-servo-2").slider('getValue'));
            //console.log("F3 Value: "+$("#fish-servo-3").slider('getValue'));
             // Nothing to do
            break;
        default:
            break;
    }       
}

function writeElephantValues(keyVal)
{
    console.log("Call writeElephantValues");
    switch (keyVal[0])
    {
        case valueIds[0]:
            //document.getElementById(elephantIds[0]).value = keyVal[1];
            $('#ele-servo-1').slider('setValue', keyVal[1],true);
            break;
        case valueIds[1]:
            //ment.getElementById(elephantIds[1]).value = keyVal[1];
            $('#ele-servo-2').slider('setValue', keyVal[1],true);
            break;
        case valueIds[2]:
            //document.getElementById(elephantIds[2]).value = keyVal[1];
            $('#ele-servo-3').slider('setValue', keyVal[1],true);
            break;
        case valueIds[3]:
            //document.getElementById(elephantIds[3]).value = keyVal[1];
            $('#ele-servo-4').slider('setValue', keyVal[1],true);
            break;
        default:
            break;
    }      
}

function writeChameleonValues(keyVal)
{
    console.log("Call writeElephantValues");
    switch (keyVal[0])
    {
        case valueIds[0]:
            //document.getElementById(chameleonIds[0]).value = keyVal[1];
            $('#cha-servo-1').slider('setValue', keyVal[1],true);
            break;
        case valueIds[1]:
            // Nothing to do yet for chameleon project
            break;
        case valueIds[2]:
            // Nothing to do yet for chameleon project
            break;
        case valueIds[3]:
            // Nothing to do yet for chameleon project
            break;
        default:
            break;
    }      
}
