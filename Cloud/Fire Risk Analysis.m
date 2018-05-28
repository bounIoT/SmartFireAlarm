channelID=494213;
readKey='CP8DCPU82JRI7A9Q';

smokeThresh=400;
gasThresh=400;
tempThresh=55;
humidThresh=25;
humidTempThresh=35;

iftttURL='https://maker.ifttt.com/trigger/fire/with/key/h7-ouMecbB7125b0SnAyzIAHS_66vvKbPI8y1rJz1t7';
[data,timestamps]=thingSpeakRead(channelID,'ReadKey',readKey);


if(minutes(10)<(datetime('now')-timestamps))
    webwrite(iftttURL,'value1','Sensor not Working');  
    return
end

gas=0;
heat=0;
hum=0;

if (data(1)>tempThresh)
    heat=1;
end

if (data(2)<humidThresh & data(1)>humidTempThresh)
    hum=1;
end

if (data(4)>gasThresh)
    gas=1;
end

alert=heat|hum|gas;

if(alert)
    alertString='Message: '
    if(heat==1)
        alertString=strcat(alertString,'Very High Temperature, ')
    end
    if(hum==1)
        alertString=strcat(alertString,' Low Humidity, ')
    end
    if(gas==1)
        alertString=strcat(alertString,' Flammable Gas, ')
    end
    
    webwrite(iftttURL,'value1',alertString);    
end
