#pragma once

const char defaultPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
    <head>
        <style>
            * {
                font-family: sans-serif;
            }
            body, html {
                margin: 0;
                padding: 0;
            }
            table, #page {
                margin-left: auto;
                margin-right: auto;
            }
            legend {
                font-size: x-small;
                font-weight: normal;
                color: grey;
            }
            td >  button {
                width: 100%;
                height: 100%;
            }
            body {
                height: 20em;
            }
            #page {
                width: max-content;
                margin-top: 50vh; /* poussé de la moitié de hauteur de viewport */
                transform: translateY(-50%);
            }
        </style>
        <script src="https://kit.fontawesome.com/52ac5a2d37.js" crossorigin="anonymous"></script>
        <title>Arduino Car</title>
    </head>
    <body>
        <div id="page">
            <fieldset>
                <legend>CONTROLS</legend>
                <table>
                    <tr>
                        <td></td>
                        <td>
                            <button id="forward" class="btn btn-default"><i class="fas fa-arrow-up"></i></button>
                            <script type="text/javascript">
                                document.getElementById("forward").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/move/forward', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td></td>
                    </tr>
                    <tr>
                        <td>
                            <button id="rotate_left" class="btn btn-default"><i class="fas fa-arrow-left"></i></button>
                            <script type="text/javascript">
                                document.getElementById("rotate_left").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/move/rotate/left', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="stop" class="btn btn-default"><i class="fas fa-times"></i></button>
                            <script type="text/javascript">
                                document.getElementById("stop").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/move/stop', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="rotate_right" class="btn btn-default"><i class="fas fa-arrow-right"></i></button>
                            <script type="text/javascript">
                                document.getElementById("rotate_right").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/move/rotate/right', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                    </tr>
                    <tr>
                        <td></td>
                        <td>
                            <button id="backward" class="btn btn-default"><i class="fas fa-arrow-down"></i></button>
                            <script type="text/javascript">
                                document.getElementById("backward").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/move/backward', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td></td>
                    </tr>
                </table>
            </fieldset>
            <fieldset>
                <legend>SPEED</legend>
                <table>
                    <tr>
                        <td>
                            <button id="speed_decrease" class="btn btn-default"><i class="fas fa-minus"></i></button>
                            <script type="text/javascript">
                                document.getElementById("speed_decrease").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/speed/decrease', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="speed_increase" class="btn btn-default"><i class="fas fa-plus"></i></button>
                            <script type="text/javascript">
                                document.getElementById("speed_increase").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/speed/increase', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="min_speed" class="btn btn-default">MIN</button>
                            <script type="text/javascript">
                                document.getElementById("min_speed").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/speed/min', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="max_speed" class="btn btn-default">MAX</button>
                            <script type="text/javascript">
                                document.getElementById("max_speed").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/speed/max', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                    </tr>
                </table>
            </fieldset>
            <fieldset>
                <legend>LIGHT</legend>
                <table>
                    <tr>
                        <td>
                            <button id="light_all" class="btn btn-default">ON</button>
                            <script type="text/javascript">
                                document.getElementById("light_all").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/light/all', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="light_front" class="btn btn-default">FRONT</button>
                            <script type="text/javascript">
                                document.getElementById("light_front").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/light/front', true);
                                    xhr.send();
                                }, false); 
                            </script>
                        </td>
                        <td>
                            <button id="light_back" class="btn btn-default">BACK</button>
                            <script type="text/javascript">
                                document.getElementById("light_back").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/light/back', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                        <td>
                            <button id="light_blink" class="btn btn-default">BLINK</button>
                            <script type="text/javascript">
                                document.getElementById("light_blink").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/light/blink', true);
                                    xhr.send();
                                }, false); 
                            </script>
                        </td>
                        <td>
                            <button id="light_off" class="btn btn-default">OFF</button>
                            <script type="text/javascript">
                                document.getElementById("light_off").addEventListener("click", function() {
                                    var xhr = new XMLHttpRequest();
                                    xhr.open('post', '/light/off', true);
                                    xhr.send();
                                }, false);
                            </script>
                        </td>
                    </tr>
                </table>
            </fieldset>
        </div>
        
    </body>
</html>
)=====";
