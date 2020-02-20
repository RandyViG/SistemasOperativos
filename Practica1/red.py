#!/usr/bin/env python3
import subprocess as sub
import os
ifConfig = sub.run(['ifconfig'],stdout=sub.PIPE)
ifConfigText = ifConfig.stdout.decode('utf-8').split('\n')

text = "".join(ifConfigText)
index = text.find("BROADCAST,RUNNING,MULTICAST>  mtu 1500")

ipFilter=text[index+51:index+51+25].split(' ')
ip = ipFilter[0]
print('La ip es: {}'.format(ip))

auxIp = ip[::-1]
host = auxIp.find('.')
red = ip[:-host]
print('La red es: {}'.format(red))
enabled = [ ]
disabled = [ ]

for host in range(85,87):
    response = sub.run(['ping','-c 1',red+str(host)],stdout=sub.PIPE,stderr=sub.PIPE)
    response = response.returncode

    if response == 0:
        enabled.append(red+str(host))
    else:
        disabled.append(red+str(host))

print('Ip conectadas')
for en in enabled:
    print(en)

print('Ip desconectadas')
for dis in disabled:
    print(dis)

for ip in enabled:
    copy = 'sshpas -p alumno scp /home/randy/Documentos/Operativos/Practica1/backup.py '
    target = 'alumno@'+ ip
    permission = 'chmod +x /home/alumno/backup.py'
    connect = 'sshpass -p alumno ssh ' + target
    run = 'python3 /home/alumno/backup.py'
    backup = 'sshpass -p alumno scp ' + target + ':/home/alumno/backup.tar.gz /home/randy/Documentos/Operativos'
    rename = 'mv /home/randy/Documentos/Operativos/backup.tar.gz /home/randy/Documentos/Operativos/'+ip+'.tar.gz''

    os.system( copy + target + ':/home/alumno' )
    os.system( connect + ' ' + permission )
    os.system( connect + ' ' + run )
    os.system( backup )
    os.system( rename )