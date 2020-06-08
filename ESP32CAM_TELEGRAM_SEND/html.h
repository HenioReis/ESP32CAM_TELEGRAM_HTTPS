static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width,initial-scale=1">
        <script src="https:\/\/ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js"></script>
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">        
        <title>ESP32CAM MULTIFUNÇÃO</title>
        <style>
           body {
                font-family: Arial,Helvetica,sans-serif;
                background: #181818;
                color: #EFEFEF;
                font-size: 17px
            }

            h2 {
                font-size: 18px
            }

            section.main {
                display: flex
            }

            #menu,section.main {
                flex-direction: column
            }

            #menu {
                display: none;
                flex-wrap: nowrap;
                min-width: 340px;
                background: #363636;
                padding: 10px;
                border-radius: 7px;
                margin-top: -5px;
                margin-right: 10px;
            }

            #content {
                display: flex;
                flex-wrap: wrap;
                align-items: stretch
            }

            figure {
                padding: 0px;
                margin: 0;
                -webkit-margin-before: 0;
                margin-block-start: 0;
                -webkit-margin-after: 0;
                margin-block-end: 0;
                -webkit-margin-start: 0;
                margin-inline-start: 0;
                -webkit-margin-end: 0;
                margin-inline-end: 0
            }

            figure img {
                display: block;
                width: 100%;
                height: auto;
                border-radius: 4px;
                margin-top: 8px;
            }

            @media (min-width: 800px) and (orientation:landscape) {
                #content {
                    display:flex;
                    flex-wrap: nowrap;
                    align-items: stretch
                }

                figure img {
                    display: block;
                    max-width: 100%;
                    max-height: calc(100vh - 40px);
                    width: auto;
                    height: auto
                }

                figure {
                    padding: 0 0 0 0px;
                    margin: 0;
                    -webkit-margin-before: 0;
                    margin-block-start: 0;
                    -webkit-margin-after: 0;
                    margin-block-end: 0;
                    -webkit-margin-start: 0;
                    margin-inline-start: 0;
                    -webkit-margin-end: 0;
                    margin-inline-end: 0
                }
            }

            section#buttons {
                display: flex;
                flex-wrap: nowrap;
                justify-content: space-between
            }

            #nav-toggle {
                cursor: pointer;
                display: block
            }

            #nav-toggle-cb {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0
            }

            #nav-toggle-cb:checked+#menu {
                display: flex
            }

            .input-group {
                display: flex;
                flex-wrap: nowrap;
                line-height: 22px;
                margin: 5px 0
            }

            .input-group>label {
                display: inline-block;
                padding-right: 10px;
                min-width: 47%
            }

            .input-group input,.input-group select {
                flex-grow: 1
            }

            .range-max,.range-min {
                display: inline-block;
                padding: 0 5px
            }

            button {
                display: block;
                margin: 5px;
                padding: 0 12px;
                border: 0;
                line-height: 28px;
                cursor: pointer;
                color: #fff;
                background: #171515;
                border-radius: 5px;
                font-size: 16px;
                outline: 0
            }

            button:hover {
                background: #1dbf58
            }

            button:active {
                background: #4952fc
            }

            button.disabled {
                cursor: default;
                background: #a0a0a0
            }

            input[type=range] {
                -webkit-appearance: none;
                width: 100%;
                height: 22px;
                background: #363636;
                cursor: pointer;
                margin: 0
            }

            input[type=range]:focus {
                outline: 0
            }

            input[type=range]::-webkit-slider-runnable-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #EFEFEF;
                border-radius: 0;
                border: 0 solid #EFEFEF
            }

            input[type=range]::-webkit-slider-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
                -webkit-appearance: none;
                margin-top: -11.5px
            }

            input[type=range]:focus::-webkit-slider-runnable-track {
                background: #EFEFEF
            }

            input[type=range]::-moz-range-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #EFEFEF;
                border-radius: 0;
                border: 0 solid #EFEFEF
            }

            input[type=range]::-moz-range-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer
            }

            input[type=range]::-ms-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: 0 0;
                border-color: transparent;
                color: transparent
            }

            input[type=range]::-ms-fill-lower {
                background: #EFEFEF;
                border: 0 solid #EFEFEF;
                border-radius: 0
            }

            input[type=range]::-ms-fill-upper {
                background: #EFEFEF;
                border: 0 solid #EFEFEF;
                border-radius: 0
            }

            input[type=range]::-ms-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #ff3034;
                cursor: pointer;
                height: 2px
            }

            input[type=range]:focus::-ms-fill-lower {
                background: #EFEFEF
            }

            input[type=range]:focus::-ms-fill-upper {
                background: #363636
            }

            .switch {
                display: block;
                position: relative;
                line-height: 22px;
                font-size: 16px;
                height: 22px
            }

            .switch input {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0
            }

            .slider {
                width: 50px;
                height: 22px;
                border-radius: 22px;
                cursor: pointer;
                background-color: grey
            }

            .slider,.slider:before {
                display: inline-block;
                transition: .4s
            }

            .slider:before {
                position: relative;
                content: "";
                border-radius: 50%;
                height: 16px;
                width: 16px;
                left: 4px;
                top: 3px;
                background-color: #fff
            }

            input:checked+.slider {
                background-color: #ff3034
            }

            input:checked+.slider:before {
                -webkit-transform: translateX(26px);
                transform: translateX(26px)
            }

            select {
                border: 1px solid #363636;
                font-size: 14px;
                height: 22px;
                outline: 0;
                border-radius: 5px
            }

            .image-container {
                position: relative;
                min-width: 160px
            }

            .close {
                position: absolute;
                right: 5px;
                top: 5px;
                background: #ff3034;
                width: 16px;
                height: 16px;
                border-radius: 100px;
                color: #fff;
                text-align: center;
                line-height: 18px;
                cursor: pointer
            }

            .hidden {
                display: none
            }
            input[type=text]{
                padding: 9px;
                text-align: center;
                height: 10px;
                width: 100px;
            }

            #tel{
               color:#0088CC; 
            }
            #stream{
                border-radius: 2px solid;
                background: #181818;
                box-shadow: 0px 0px 5px 5px;
             }
            .responsive {
             width: 100%;
             height: auto;
            }      
        </style>        
    </head>
    <body>
          <section class="main">        
          <div id="logo">
          <label for="nav-toggle-cb" id="nav-toggle">&#9776;&nbsp;&nbsp;ESP32CAM MULTIFUNÇÃO</label>
          </div>
          <div id="content">
          <div id="sidebar">
          <input type="checkbox" id="nav-toggle-cb" checked="checked">
          <nav id="menu">
          <div>
                <div class="input-group" id="framesize-group">
                <label for="framesize">Resolução</label>
                <select id="framesize" onclick="try{fetch(document.location.origin+'/?framesize='+this.value);}catch(e){}">
                    <option value="UXGA">UXGA(1600x1200)</option>
                    <option value="SXGA">SXGA(1280x1024)</option>
                    <option value="XGA">XGA(1024x768)</option>
                    <option value="SVGA">SVGA(800x600)</option>
                    <option value="VGA">VGA(640x480)</option>
                    <option value="CIF">CIF(400x296)</option>
                    <option value="QVGA" selected="selected">QVGA(320x240)</option>
                    <option value="HQVGA">HQVGA(240x176)</option>
                    <option value="QQVGA">QQVGA(160x120)</option>
                </select> 
                </div>
                <div class="input-group" id="modelo-especial-group">
                  <label for="modelo-especial">Modelo (Padrão)</label>
                    <select id="model-padrao" class="default-action">
                        <option value="1" selected="selected">Escolha Modelo</option>
                        <option value="2">Objection Detection</option>
                        <option value="3">Position</option>
                        <option value="4">Classif</option>
                        <option value="5">Opção</option>
                    </select>
                </div>
               <div class="input-group" id="redesocial-group">
                    <label for="redesocial">Banco de Dados/Rede Social</label>
                    <select id="canal" class="default-action">
                       <option value="1"selected="selected"">Escolha Canal</option>
                       <option value="2">Telegram</option>
                       <option value="3">Line Notify</option>
                       <option value="4">Google Drive</option>
                       <option value="5">DB MySCL</option>
                    </select>
              </div>
              <div class="input-group" id="rotacao-esp32cam-group">
                  <label for="rotacao">Rotação</label>
                  <select onchange="document.getElementById('stream').style.transform='rotate('+this.value+')';">
                      <option value="0deg">0 Grau</option>
                      <option value="90deg">90 Grau</option>
                      <option value="180deg">180 Grau</option>
                      <option value="270deg">270 Grau</option>
                  </select>
                </div>
              <div id="telegram-container" class="telegram-container" style="display:none;">
                   <i class="fa fa-telegram fa-2x" id="tel"></i>
                     <label for="token">Token:</label>
                     <input type="text" id="token" value="">
                     <label for="chat_id">Chat ID:</label>
                     <input type="text" id="chat_id" value="">
                   <section id="buttons">
                       <button id="toggle_telegram">Send Telegram</button>
                   </section>
             </div>
                   <section id="buttons">
                       <button id="toggle-stream">Stream</button>
                       <button id="toggle-stop">Stop</button>
                   </section>
             </nav>
             </div>
                <figure>
                  <div id="stream-container" class="image-container">
                    <label>TELA ESP32CAM OV2460</label>
                    <img id="stream" src="" style="" class="responsive">
                  </div>
                  <div id="messege" style=""><div>
                </figure>
            </div>
        </section>    
    </body>
    <script>
      var ViewStream = document.getElementById('stream');
      var IniciaStream = document.getElementById('toggle-stream');
      var StopStream = document.getElementById('toggle-stop');      
      var Sendtelegram = document.getElementById('toggle_telegram');
      var token = document.getElementById('token');
      var chat_id = document.getElementById('chat_id');
      var Messege = document.getElementById('messege');
      var Timer;
      var State = false;
       
       IniciaStream.onclick = function (event) {
        State=true;
        ViewStream.onload = function (event) {
          clearInterval(Timer);
          if (State==true) {
            setTimeout(function(){IniciaStream.click();},100);
            Timer = setInterval(function(){IniciaStream.click();},10000);
          }
          else
            ViewStream.src="";
        }        
        ViewStream.src=location.origin+'/?Stream='+Math.random();    
      }
  
      StopStream.onclick = function (event) {
        clearInterval(Timer);
        State=false;  
        ViewStream.onload = function (event) {}             
        ViewStream.src="";
      }
                    
      Sendtelegram.onclick = function (event) {
        Messege.innerHTML='SENDING...';
        SendTelegramPhoto(location.origin+'/?Sendphoto='+token.value+';'+chat_id.value+';'+(new Date().getFullYear()*10000000000+(new Date().getMonth()+1)*100000000+new Date().getDate()*1000000+new Date().getHours()*10000+new Date().getMinutes()*100+new Date().getSeconds()+new Date().getSeconds()*0.001).toString());
      }      
      function SendTelegramPhoto(Parth) {
        var Url;
        Url = Parth;
        var request = new XMLHttpRequest();
        request.open("GET", Url, true);
        request.send();
        Messege.innerHTML='';
      }
      
      window.onload=function(){
      document.getElementById('canal').addEventListener('change', function () {
      var style = this.value == 2 ? 'block' : 'none';
      document.getElementById('telegram-container').style.display = style;
        });
      }
    </script>
</html>
)rawliteral";
