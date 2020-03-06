import subprocess as sub
import os

users = []
passwords = []
ips=[]

while(True):

    for i,user in enumerate(users):
        copy = 'sshpass -p' + passwords[i] + ' scp /home/randy/Documentos/Operativos/Imagen/calleBN.bmp'
        make = 'mkdir /home/' + user +'/Imagen'
        target = user + '@' +  ips[i]
        pathBackup = target + ':/home/'+users[i]+'/Imagen'
        connect = 'sshpass -p ' + passwords[i] +' ssh ' + target
        find = connect + ' find /home/' + user + 'Imagen/calleBN.bmp'

        print(user)
        print(ips[i])
        try:
            validate = sub.run([find],stdout=sub.PIPE)
            validate = validate.stdout.decode('utf-8')
            if( validate == ''):
                continue
        except:
            os.system( connect + ' ' + make )
            os.system( copy+ ' '+ pathBackup )

