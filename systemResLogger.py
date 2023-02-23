import psutil
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
from infi.systray import SysTrayIcon

cred = credentials.Certificate("./firebase/firebase.json")
firebase_admin.initialize_app(cred,{
    'databaseURL':'https://iot-p-18286-default-rtdb.asia-southeast1.firebasedatabase.app/'
})

ON = False
def stop(systray):
    global ON
    ON = False

def startTray():
    global ON
    ON = True
    systray.start()

# menu_options = (("Stop Logging", None, stop),)
systray = SysTrayIcon("icon.ico", "Resource Logger", None, on_quit=stop)
startTray()

print(ON)

ref = db.reference('/')

while ON:
    cpu = psutil.cpu_percent(1)
    ram = psutil.virtual_memory()[2]
    ram2 = psutil.virtual_memory()[3]
    ram2 = round(ram2/1000000000, 2)
    print("CPU Usage",cpu,"%", "RAM Usage", ram,"%",ram2 ,"GB Used")

    ref.update({
    'data' : {
        'cpu' : cpu,
        'ram' : ram,
        'ram2': ram2
        }
    })
    
systray.shutdown()
