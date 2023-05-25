#############################################################################
## Designed and Written by Fernando Martínez-García and Jesús Tamez-Duque. ##
##        Copyright INDI Ingénierie et Design SAS France, 2019-2021.       ##
#############################################################################


# -*- coding: utf-8 -*-
import tkinter as tk
from PIL import Image
from PIL import ImageTk
import tkinter.ttk as ttk
import serial
import serial.tools.list_ports
import time
from pylsl import StreamInfo, StreamOutlet

time_out_handshake=0.1
time_out_handshake2=9

button_font = (("Titilium web"),10)
indi_blue = '#28b9a6'
indi_red = '#c42231'
indi_purple = '#802f7d'
indi_yellow = '#edb22e'

init_position = (0,0)
init_sticky = ''
init_rowspan = 1
init_columnspan = 1
init_padding = (0,0)
init_button_padding = (10,10)
init_ipadding = (0,0)


class frame(tk.Frame):
    def __init__(self, position, sticky, rowspan, columnspan, padding, ipadding, *args, **kwargs):
        self.position = position
        self.sticky = sticky
        self.columnspan = columnspan
        self.rowspan = rowspan
        self.padding = padding
        self.ipadding = ipadding
        super(frame, self).__init__(*args, **kwargs)
    
    def reset(self):
        self.position = init_position
        self.sticky = init_sticky
        self.columnspan = init_columnspan
        self.rowspan = init_rowspan
        self.padding = init_padding
        self.ipadding = init_ipadding  

class button(tk.Button):
    def __init__(self, position, sticky, rowspan, columnspan, padding, ipadding, *args, **kwargs):
        self.position = position
        self.sticky = sticky
        self.columnspan = columnspan
        self.rowspan = rowspan
        self.padding = padding
        self.ipadding = ipadding
        super(button, self).__init__(*args, **kwargs)
        
    def reset(self):
        self.position = init_position
        self.sticky = init_sticky
        self.columnspan = init_columnspan
        self.rowspan = init_rowspan
        self.padding = init_padding
        self.ipadding = init_ipadding

class label(tk.Label):
    def __init__(self, position, sticky, rowspan, columnspan, padding, ipadding, size, *args, **kwargs):
        self.position = position
        self.sticky = sticky
        self.columnspan = columnspan
        self.rowspan = rowspan
        self.padding = padding
        self.ipadding = ipadding
        super(label, self).__init__(*args, **kwargs, font=(("Titilium web"),size))
        
    def reset(self):
        self.position = init_position
        self.sticky = init_sticky
        self.columnspan = init_columnspan
        self.rowspan = init_rowspan
        self.padding = init_padding
        self.ipadding = init_ipadding

class image_label(tk.Label):
    def __init__(self, position, sticky, rowspan, columnspan, padding, ipadding, *args, **kwargs):
        self.position = position
        self.sticky = sticky
        self.columnspan = columnspan
        self.rowspan = rowspan
        self.padding = padding
        self.ipadding = ipadding
        super(image_label, self).__init__(*args, **kwargs)
        
    def reset(self):
        self.position = init_position
        self.sticky = init_sticky
        self.columnspan = init_columnspan
        self.rowspan = init_rowspan
        self.padding = init_padding
        self.ipadding = init_ipadding

class combobox(ttk.Combobox):
    def __init__(self, position, sticky, rowspan, columnspan, padding, ipadding, *args, **kwargs):
        self.position = position
        self.sticky = sticky
        self.columnspan = columnspan
        self.rowspan = rowspan
        self.padding = padding
        self.ipadding = ipadding
        super(combobox, self).__init__(*args, **kwargs)

    def reset(self):
        self.position = init_position
        self.sticky = init_sticky
        self.columnspan = init_columnspan
        self.rowspan = init_rowspan
        self.padding = init_padding
        self.ipadding = init_ipadding

def Close_Main(win):
    if ser.isOpen() == True:
        ser.close()
    win.destroy()
    
def _delete_window():
    None

#####################Arduino-Handshake functions################################
def send_instruction_main(message_si,test=False):
    w_si=ord(message_si)
    Flag_HPA=Handshake_Pyth_Ard(w_si)
    if Flag_HPA==1:
        Flag_HAP=Handshake_Ard_Python(0)

def send_instruction(message_si,Label_si,Flag_label_si,hierarchy_level,test=False):  # interacting with GUI
    walk_repetition=0
    message_si_lsl=message_si
    if message_si == 'W':
        message_si = labelNumberSteps_StandMenu['text']
        walk_repetition=ord(message_si)-48
        #walk_repetition=max(walk_repetition,1)
    w_si=ord(message_si) # ord function converting characters to integers
    Flag_HPA=Handshake_Pyth_Ard(w_si) #1 uncomment to test
    #print([message_si,hierarchy_level])
    if test:
        return 0
    elif Flag_HPA==0:
        if Flag_label_si==1:
            Label_si.config(text = "Try again",fg="darkred")
    else:
        if Flag_label_si==1:
            
            outlet.push_chunk([marker_s+message_si_lsl])#Sending list of strings withing a list
                                                    #to indicate that the movement has finished.
            print([marker_s+message_si_lsl])
            #time.sleep(0.5)#waiting for half a second.
            
            Flag_HAP=Handshake_Ard_Python(walk_repetition) # receiving confirmation from arduino after movements performed (9 seconds).
            if Flag_HAP==0:
                Label_si.config(text = "Try again",fg="darkred") # Ready to try again - user friendly 'fail'.
            else:
                Label_si.config(text = "Movement Finished",fg="#28b9a6")
                
                #outlet.push_sample([markernames[1]])#Sending one string withing a list, interpreted as a pointer,
                                                    # to indicate that the movement has finished.
                outlet.push_chunk([marker_f+message_si_lsl])#Sending list of strings withing a list
                                                    #to indicate that the movement has finished.
                print([marker_f+message_si_lsl])
                time.sleep(0.2)#waiting for 0.2 seconds.

def Handshake_Pyth_Ard(number_int_sent, test=False):
    Number_trials=0
    Flag_success=0
    if test:
        return Flag_success
    else:
        while (Number_trials<5): # try to send message 5 times or give up
            nis_Flag_2B=(0).to_bytes(2, byteorder='big') # converting 0 to bytes
            nis_2B=(number_int_sent).to_bytes(2, byteorder='big') # converting the message into bytes
            ser.write(nis_2B) # sending to serial
            #print(number_int_sent) # printing the message (not required but for info)
    
            #t0=time.clock()
            t0=time.perf_counter()
            while ((ser.in_waiting<2)and(time.perf_counter()-t0<time_out_handshake)): # waiting for arduino reply - 2 bytes integer
            #while ((ser.in_waiting<2)and(time.clock()-t0<time_out_handshake)): # waiting for arduino reply - 2 bytes integer
                None
    
            if ser.in_waiting==2: #2 bytes received
                number_int_recieve=int.from_bytes(ser.read(2),byteorder='big')
                if number_int_recieve==number_int_sent: # Arduino replied same number ?
                    nis_Flag_2B=(1777).to_bytes(2, byteorder='big') # everything is fine so I send 1777
                    Flag_success=1
                    ser.write(nis_Flag_2B)
                    #print("perfect")
                    #print(number_int_recieve)
                    return Flag_success
                    break
                else:
                    Flag_success=0
                    #print("error")
                    #print(number_int_recieve)
            else:
                while(ser.in_waiting>0):
                    ser.read(1) # getting rid of unwanted bytes
                Flag_success=0
                #print("Time_out")
                #print(time.clock()-t0)
                #print(ser.in_waiting)
            Number_trials=Number_trials+1
            time.sleep(time_out_handshake/2) # delay because time might me too short - avoid errors
        return Flag_success

def Handshake_Ard_Python(number_repetitions):
    # Calling this function when I know Arduino is sending information
    # Protocol to receive a 2 bytes integer in arduino

  number_repetitions=max(number_repetitions,1)
  while (number_repetitions>0):
      #t0=time.clock() # asking time to the laptop in seconds
      t0=time.perf_counter()
      while ((ser.in_waiting<2)and(time.perf_counter()-t0<time_out_handshake2)): # waiting 9 seconds (time_out_handshake2) if nothing received, giving up - 9 seconds for the movement
      #while ((ser.in_waiting<2)and(time.clock()-t0<time_out_handshake2)): # waiting 9 seconds (time_out_handshake2) if nothing received, giving up - 9 seconds for the movement
        None


      if ser.in_waiting==2: # 2 bytes received
        number_int_recieve=int.from_bytes(ser.read(2),byteorder='big') # converting the 2 bytes from arduino into integer understood by python
        if number_int_recieve==1888: # confirmation code for handshake
          Flag_success=1
          #print("perfect r")
          #print(number_int_recieve)
        else:
          Flag_success=0
          #print("error r")
          #print(number_int_recieve)
      else: # time expired
        while(ser.in_waiting>0): # if only 1 byte
            ser.read(1) # read to get rid of the byte
        Flag_success=0
        #print("Time_out r") # r = received
        #print(time.clock()-t0)
        #print(ser.in_waiting) # no bytes left
      number_repetitions=number_repetitions-1
  return Flag_success
################################################################################

#######################Port connection functions################################
def Available_serial_ports():
    all_ports_list=serial.tools.list_ports.comports()
    Name_ports=[]
    for i in range(len(all_ports_list)):
        Name_ports.append(all_ports_list[i].device)
    return Name_ports

def Connect_to_port(Selected_port,ser,botton,test=False):
    # or get selection directly from combobox
    Port_to_connect=Selected_port.get()
    ser.port = Port_to_connect
    # # open port if not already open
    if not test:
        if ser.isOpen() == False:
            try:
                ser.open()
                if ser.isOpen()==True:
                    #print(Port_to_connect)
                    labelStateProcess.config(text="Connected", fg=indi_blue)
                    botton["state"]="normal"
                    botton.config(bg=indi_blue)
            except serial.SerialException:
                labelStateProcess.config(text='Not Connected, Try again', fg=indi_red)
                botton["state"]="disable"
    else:
        labelStateProcess.config(text="Connected", fg=indi_blue)
        botton["state"]="normal"
        botton.config(bg=indi_blue)
################################################################################

def enable_buttons(en_button_list, button_color=indi_blue):
    for button in en_button_list:
        button["state"] = "normal"
        button.config(bg=button_color, fg='white')

def disable_buttons(button_list, button_color='white'):
    for button in button_list:
        button["state"]="disabled"
        button.config(bg=button_color, fg='gray')

def create_grid(frame, widgets, rows=0, columns=0):
    current_size = frame.grid_size()
    if current_size[1]>rows:
        for r in range(rows,current_size[1]):
            frame.rowconfigure(r, weight=0)
    if current_size[0]>columns:
        for c in range(columns, current_size[0]):
            frame.columnconfigure(c, weight=0)
    for r in range(rows):
        frame.rowconfigure(r, weight=1)
    for c in range(columns):
        frame.columnconfigure(c, weight=1)
    for w in widgets:
        w.grid(row=w.position[0], column=w.position[1], padx=w.padding[0], pady=w.padding[1], ipadx=w.ipadding[0], ipady=w.ipadding[1], sticky=w.sticky, rowspan=w.rowspan, columnspan=w.columnspan)
        
def create_window():
    window = tk.Tk()
    window.title("   Alice Exoskeleton")
    window.iconbitmap("Logo.ico")
    window.minsize(400, 550)
    window.geometry("600x550")
    window.config(background='white')
    return window

def init_images(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global alice_not_connected, Alice_not_connected
    global alice_stand_waiting, Alice_stand_waiting
    global alice_sit_waiting, Alice_sit_waiting
    global alice_stand_straight, Alice_stand_straight
    global plus, Plus
    global minus, Minus
    global alice_sit_straight, Alice_sit_straight
    global alice_gait_training, Alice_gait_training
    global alice_step_one, alice_step_two, alice_step_three, alice_step_four, alice_step_five
    global alice_standing_exercises, Alice_standing_exercises
    global alice_left_backwards, alice_left_forwards
    global alice_right_backwards, alice_right_forwards
    global alice_sitting_exercises, Alice_sitting_exercises
    global alice_left_bend, alice_left_extend
    global alice_right_bend, alice_right_extend
    global alice_both_bend, alice_both_extend

    alice_not_connected = Image.open("Alice_not_connected.png")
    alice_not_connected = alice_not_connected.resize((180,230), Image.ANTIALIAS)
    alice_not_connected = ImageTk.PhotoImage(master=app, image=alice_not_connected)
    Alice_not_connected = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                      master=app, image=alice_not_connected, bd=0)

    alice_stand_waiting = Image.open("Alice_stand_waiting.png")
    alice_stand_waiting = alice_stand_waiting.resize((110,200), Image.ANTIALIAS)
    alice_stand_waiting = ImageTk.PhotoImage(master=app, image=alice_stand_waiting)
    Alice_stand_waiting = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                      master=app, image=alice_stand_waiting, bd=0)

    alice_sit_waiting = Image.open("Alice_sit_waiting.png")
    alice_sit_waiting = alice_sit_waiting.resize((90,170), Image.ANTIALIAS)
    alice_sit_waiting = ImageTk.PhotoImage(master=app, image=alice_sit_waiting)
    Alice_sit_waiting = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                    master=app, image=alice_sit_waiting, bd=0)

    alice_stand_straight = Image.open("Alice_stand_straight.png")
    alice_stand_straight = alice_stand_straight.resize((110,200), Image.ANTIALIAS)
    alice_stand_straight = ImageTk.PhotoImage(master=app, image=alice_stand_straight)
    Alice_stand_straight = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                       master=app, image=alice_stand_straight, bd=0)

    alice_sit_straight = Image.open("Alice_sit_straight.png")
    alice_sit_straight = alice_sit_straight.resize((100,180), Image.ANTIALIAS)
    alice_sit_straight = ImageTk.PhotoImage(master=app, image=alice_sit_straight)
    Alice_sit_straight = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                     master=app, image=alice_sit_straight, bd=0)

    alice_gait_training = Image.open("Alice_gait_training.png")
    alice_gait_training = alice_gait_training.resize((180,200), Image.ANTIALIAS)
    alice_gait_training = ImageTk.PhotoImage(master=app, image=alice_gait_training)
    Alice_gait_training = image_label((0,1), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                     master=app, image=alice_gait_training, bd=0)
    alice_step_one = Image.open("Alice_step_one.png")
    alice_step_one = alice_step_one.resize((180,200), Image.ANTIALIAS)
    alice_step_one = ImageTk.PhotoImage(master=app, image=alice_step_one)
    alice_step_two = Image.open("Alice_step_two.png")
    alice_step_two = alice_step_two.resize((180,200), Image.ANTIALIAS)
    alice_step_two = ImageTk.PhotoImage(master=app, image=alice_step_two)
    alice_step_three = Image.open("Alice_step_three.png")
    alice_step_three = alice_step_three.resize((180,200), Image.ANTIALIAS)
    alice_step_three = ImageTk.PhotoImage(master=app, image=alice_step_three)
    alice_step_four = Image.open("Alice_step_four.png")
    alice_step_four = alice_step_four.resize((180,200), Image.ANTIALIAS)
    alice_step_four = ImageTk.PhotoImage(master=app, image=alice_step_four)
    alice_step_five = Image.open("Alice_step_five.png")
    alice_step_five = alice_step_five.resize((180,200), Image.ANTIALIAS)
    alice_step_five = ImageTk.PhotoImage(master=app, image=alice_step_five)

    plus = Image.open("plus.png")
    plus = plus.resize((10,10), Image.ANTIALIAS)
    Plus = ImageTk.PhotoImage(master=app, image=plus)

    minus = Image.open("minus.png")
    minus = minus.resize((10,10), Image.ANTIALIAS)
    Minus = ImageTk.PhotoImage(master=app, image=minus)
    
    alice_standing_exercises = Image.open("Alice_standing_exercises.png")
    alice_standing_exercises = alice_standing_exercises.resize((180,200), Image.ANTIALIAS)
    alice_standing_exercises = ImageTk.PhotoImage(master=app, image=alice_standing_exercises)
    Alice_standing_exercises = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                       master=app, image=alice_standing_exercises, bd=0)
    alice_left_backwards = Image.open("Alice_left_backwards.png")
    alice_left_backwards = alice_left_backwards.resize((180,200), Image.ANTIALIAS)
    alice_left_backwards = ImageTk.PhotoImage(master=app, image=alice_left_backwards)
    alice_left_forwards = Image.open("Alice_left_forwards.png")
    alice_left_forwards = alice_left_forwards.resize((180,200), Image.ANTIALIAS)
    alice_left_forwards = ImageTk.PhotoImage(master=app, image=alice_left_forwards)
    alice_right_backwards = Image.open("Alice_right_backwards.png")
    alice_right_backwards = alice_right_backwards.resize((180,200), Image.ANTIALIAS)
    alice_right_backwards = ImageTk.PhotoImage(master=app, image=alice_right_backwards)
    alice_right_forwards = Image.open("Alice_right_forwards.png")
    alice_right_forwards = alice_right_forwards.resize((180,200), Image.ANTIALIAS)
    alice_right_forwards = ImageTk.PhotoImage(master=app, image=alice_right_forwards)
    
    alice_sitting_exercises = Image.open("Alice_sitting_exercises.png")
    alice_sitting_exercises = alice_sitting_exercises.resize((190,190), Image.ANTIALIAS)
    alice_sitting_exercises = ImageTk.PhotoImage(master=app, image=alice_sitting_exercises)
    Alice_sitting_exercises = image_label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                                       master=app, image=alice_sitting_exercises, bd=0)
    alice_left_bend = Image.open("Alice_left_bend.png")
    alice_left_bend = alice_left_bend.resize((190,190), Image.ANTIALIAS)
    alice_left_bend = ImageTk.PhotoImage(master=app, image=alice_left_bend)
    alice_left_extend = Image.open("Alice_left_extend.png")
    alice_left_extend = alice_left_extend.resize((190,190), Image.ANTIALIAS)
    alice_left_extend = ImageTk.PhotoImage(master=app, image=alice_left_extend)
    alice_right_bend = Image.open("Alice_right_bend.png")
    alice_right_bend = alice_right_bend.resize((190,190), Image.ANTIALIAS)
    alice_right_bend = ImageTk.PhotoImage(master=app, image=alice_right_bend)
    alice_right_extend = Image.open("Alice_right_extend.png")
    alice_right_extend = alice_right_extend.resize((190,190), Image.ANTIALIAS)
    alice_right_extend = ImageTk.PhotoImage(master=app, image=alice_right_extend)
    alice_both_bend = Image.open("Alice_sitting_exercises.png")
    alice_both_bend = alice_both_bend.resize((190,190), Image.ANTIALIAS)
    alice_both_bend = ImageTk.PhotoImage(master=app, image=alice_both_bend)
    alice_both_extend = Image.open("Alice_both_extend.png")
    alice_both_extend = alice_both_extend.resize((190,190), Image.ANTIALIAS)
    alice_both_extend = ImageTk.PhotoImage(master=app, image=alice_both_extend)

def init_shared_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global mainMenuTitle
    global labelStateProcess
    global frameConnection, cb, buttonConnect
    global frameBottom, frameBottomButtons, buttonStorage, buttonExitMenu, labelCopyright, buttonHome
    global frameConnectionBottom, cbBottom, buttonConnectBottom
    global buttonConfirmStand, buttonConfirmSit
    global frameLeftLeg, labelLeftLeg
    global frameRightLeg, labelRightLeg
    global frameMainWindowBottom
    global bottonMainWindowBottom
    
    mainMenuTitle = label(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                          size=20, master=app, text='Alice Exoskeleton', bg='white', fg='black')
    labelStateProcess = label(init_position, 'n', init_rowspan, init_columnspan, (0,10), init_ipadding,
                              size=14, master=app, text="Waiting for connection", bg='white', fg=indi_red)


    frameConnection = frame(init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                            app, bg='white')
    buttonMainWindowBottom = button((1,1), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                             frameConnection, text="Main Window", fg='white',
                             command=lambda j= "-1": straight_menu())
    create_grid(frameConnection, [buttonMainWindowBottom], columns=2)
    cb = combobox((0,0), init_sticky, init_rowspan, init_columnspan, (6,0), (4,2),
                  frameConnection, values=Available_serial_ports())
    buttonConnect = button((0,1), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                           frameConnection, text="Connect", bg=indi_blue, fg='white',
                           command=lambda j= cb: Connect_to_port(j,ser,buttonMainWindowBottom))
    create_grid(frameConnection, [cb, buttonConnect], columns=2)
    
    buttonMainWindowBottom["state"]="disabled"


    frameBottom = frame(init_position, 'nsew', init_rowspan, init_columnspan, init_padding, init_ipadding,
                        app, bg='black')
    buttonHome = button((0,2), 'e', init_rowspan, 2, (10,0), (45,0),
                        frameBottom, text='Home', bg=indi_yellow, fg='black', bd=2,
                        command= lambda : straight_menu())    
    frameBottomButtons = frame((0,1), 'e', init_rowspan, init_columnspan, (10,5), init_ipadding,
                               frameBottom, bg='black')
    buttonStorage = button((0,0), 'e', init_rowspan, init_columnspan, (3,0), (10,0),
                           frameBottomButtons, text="Storage", bg='black', fg='white', bd=2,
                           command=lambda j="n": send_instruction_main(j))
    buttonExitMenu = button((0,1), 'w', init_rowspan, init_columnspan, (3,0), (12,0),
                            frameBottomButtons, text="Exit", bg='black', fg='white', bd=2,
                            command=lambda j=app: Close_Main(j))
    create_grid(frameBottomButtons, [buttonStorage, buttonExitMenu], columns=2)
    labelCopyright = label((1,0), 'w', init_rowspan, init_columnspan, (5,0), init_ipadding,
                           size=8, master=frameBottom, text="©INDI Ingénierie et Design", bg='black', fg='white')
    create_grid(frameBottom, [frameBottomButtons, labelCopyright], rows=2,columns=2)

    frameConnectionBottom = frame(init_position, 'w', init_rowspan, init_columnspan, (20,5), init_ipadding,
                                  frameBottom, bg='black')
    cbBottom = combobox((0,0), init_sticky, init_rowspan, init_columnspan, (6,0), (4,2),
                        frameConnectionBottom, values=Available_serial_ports())
    buttonConnectBottom = button((0,1), init_sticky, init_rowspan, init_columnspan, (6,0), (3,0),
                                 frameConnectionBottom, text="Connect", bg='black', fg='white',
                                 command=lambda j= cbBottom: Connect_to_port(j,ser,buttonMainWindowBottom))
    create_grid(frameConnectionBottom, [cbBottom, buttonConnectBottom], rows=1, columns=2)
    
    
    buttonConfirmStand = button(init_position, init_sticky, init_rowspan, init_columnspan, init_button_padding, init_ipadding,
                                 app, text="Confirm Stand", bg=indi_purple, fg='white',
                                 command = lambda j="S" : [send_instruction(j,labelStateProcess,1,0)])
    buttonConfirmSit = button(init_position, init_sticky, init_rowspan, init_columnspan, init_button_padding, init_ipadding,
                               app, text="Confirm Sit", bg=indi_purple, fg='white',
                               command = lambda j="Z" : [send_instruction(j,labelStateProcess,1,0)])
    
    frameLeftLeg = frame(init_position, 'e', init_rowspan, init_columnspan, init_padding, init_ipadding,
                         app, bg='white')
    labelLeftLeg = label((0,0), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                         size=10, master=frameLeftLeg, text='LEFT LEG', bg='white', fg=indi_blue)
    frameRightLeg = frame(init_position, 'w', init_rowspan, init_columnspan, init_padding, init_ipadding,
                         app, bg='white')
    labelRightLeg = label((0,0), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                         size=10, master=frameRightLeg, text='RIGHT LEG', bg='white', fg=indi_blue)
    
def init_straight_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global buttonConfirmStand_StraightMenu, buttonConfirmSit_StraightMenu
    buttonConfirmStand_StraightMenu = button(init_position, 'n', init_rowspan, init_columnspan, init_button_padding, (6,0),
                                 app, text="Confirm Stand", bg=indi_purple, fg='white',
                                 command = lambda j="S" : [stand_menu(), send_instruction(j,labelStateProcess,1,1)])
    buttonConfirmSit_StraightMenu = button(init_position, 'n', init_rowspan, init_columnspan, init_button_padding, (6,0),
                               app, text="Confirm Sit", bg=indi_purple, fg='white',
                               command = lambda j="Z" : [sit_menu(), send_instruction(j,labelStateProcess,1,1)])

def init_stand_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global buttonConfirmStand_StandMenu
    global frameStandButtons, buttonStandToSit_StandMenu, buttonWalk_StandMenu, buttonMinus_StandMenu, labelNumberSteps_StandMenu, buttonPlus_StandMenu
    global frameStandMenus, buttonGaitTraining_StandMenu, buttonStandingExercises_StandMenu
    frameStandButtons = frame(init_position, init_sticky, init_rowspan, init_columnspan, (30,0), init_ipadding,
                              app, bg='white')
    buttonStandToSit_StandMenu = button((0,0), init_sticky, init_rowspan, 4, init_button_padding, (80,0),
                              frameStandButtons, text="Sit", bg=indi_blue, fg='white',
                              command=lambda j="Y":[straight_menu(), send_instruction(j,labelStateProcess,1,1)])
    labelNumberSteps_StandMenu = label((1,2), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                           size=10, master=frameStandButtons, text='1', bg='white', fg=indi_blue)
    buttonMinus_StandMenu = button((1,1), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                         frameStandButtons, image=Minus, bd=0,
                         command=lambda j=-1 : labelNumberSteps_StandMenu.config(text=str(max(int(labelNumberSteps_StandMenu['text'])+j,0))))
    buttonPlus_StandMenu = button((1,3), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                         frameStandButtons, image=Plus, bd=0,
                         command=lambda j=1 : labelNumberSteps_StandMenu.config(text=str(min(int(labelNumberSteps_StandMenu['text'])+j,9))))
    buttonWalk_StandMenu = button((1,0), init_sticky, init_rowspan, init_columnspan, (0,10), (30,0),
                        frameStandButtons, text="Walk", bg=indi_blue, fg='white',
                        command=lambda j='W': send_instruction(j,labelStateProcess,1,1))
    create_grid(frameStandButtons, [buttonStandToSit_StandMenu,buttonWalk_StandMenu, buttonMinus_StandMenu, labelNumberSteps_StandMenu, buttonPlus_StandMenu],
                rows=2, columns=4)

    frameStandMenus = frame(init_position, init_sticky, init_rowspan, init_columnspan, (0,10), init_ipadding,
                            app, bg='white')
    labelMenu_StandMenu = label((0,0), init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding,
                           size=12, master=frameStandMenus, text="MENUS", bg='white', fg=indi_yellow)
    buttonGaitTraining_StandMenu = button((0,1), 'e', init_rowspan, init_columnspan, (20,10), (35,0),
                                frameStandMenus, text="Gait Training", bg=indi_yellow, fg='black',
                                command=lambda:gait_training_menu())
    buttonStandingExercises_StandMenu = button((0,2), 'w', init_rowspan, init_columnspan, (20,10), (20,0),
                                     frameStandMenus, text="Standing Exercises", bg=indi_yellow, fg='black',
                                     command=lambda:standing_exercises_menu())
    create_grid(frameStandMenus, [labelMenu_StandMenu, buttonGaitTraining_StandMenu,buttonStandingExercises_StandMenu],
                rows=1, columns=3)
    
def init_sit_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global buttonSitToStand_SitMenu
    global frameSitMenus, buttonSittingExercises_SitMenu

    buttonSitToStand_SitMenu = button(init_position, init_sticky, init_rowspan, init_columnspan, init_button_padding, (50,0),
                              app, text="Stand", bg=indi_blue, fg='white',
                              command=lambda j="X": [straight_menu(), send_instruction(j,labelStateProcess,1,1)])

    frameSitMenus = frame(init_position, init_sticky, init_rowspan, init_columnspan, (0,10), init_ipadding,
                            app, bg='white')
    labelMenu_SitMenu = label((0,0), init_sticky, init_rowspan, init_columnspan, (20,10), init_ipadding,
                           size=12, master=frameSitMenus, text="MENU", bg='white', fg=indi_yellow)
    buttonSittingExercises_SitMenu = button((0,1), init_sticky, init_rowspan, init_columnspan, (20,10), (25,0),
                                    frameSitMenus, text="Sitting Exercises", bg=indi_yellow, fg='black',
                                    command= lambda : sitting_exercises_menu())
    create_grid(frameSitMenus, [labelMenu_SitMenu, buttonSittingExercises_SitMenu],
                rows=1, columns=2)
    
def init_gait_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global frameGaitMenu
    global frameWalkingRoutine, buttonStepOne_GaitMenu, buttonStepTwo_GaitMenu, buttonStepThree_GaitMenu, buttonStepFour_GaitMenu, buttonStepFive_GaitMenu
    global frameSteppingRoutine, buttonConfirmStand_GaitMenu
    
    frameWalkingRoutine = frame((0,0), init_sticky, init_rowspan, init_columnspan, (60,20), init_ipadding,
                                app, bg='white')
    buttonStepOne_GaitMenu = button((1,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                           frameWalkingRoutine, text="Step 1", bg=indi_blue, fg='white',
                           command = lambda j="1":[Alice_gait_training.config(image=alice_step_one), send_instruction(j,labelStateProcess,1,1),enable_buttons([buttonStepTwo_GaitMenu]),disable_buttons([buttonStepFour_GaitMenu,buttonStepFive_GaitMenu])])
    buttonStepTwo_GaitMenu = button((2,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                           frameWalkingRoutine, text="Step 2", bg=indi_blue, fg='white',
                           command = lambda j="2":[Alice_gait_training.config(image=alice_step_two),send_instruction(j, labelStateProcess,1,1),enable_buttons([buttonStepThree_GaitMenu]),disable_buttons([buttonStepOne_GaitMenu])])
    buttonStepThree_GaitMenu = button((3,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                             frameWalkingRoutine, text="Step 3", bg=indi_blue, fg='white',
                             command = lambda j="3":[Alice_gait_training.config(image=alice_step_three),send_instruction(j,labelStateProcess,1,1),enable_buttons([buttonStepFour_GaitMenu,buttonStepFive_GaitMenu]),disable_buttons([buttonStepTwo_GaitMenu])])
    buttonStepFour_GaitMenu = button((4,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                            frameWalkingRoutine, text="Step 4", bg=indi_blue, fg='white',
                            command = lambda j="4":[Alice_gait_training.config(image=alice_step_four),send_instruction(j,labelStateProcess,1,1),enable_buttons([buttonStepOne_GaitMenu]),disable_buttons([buttonStepThree_GaitMenu,buttonStepFive_GaitMenu])])
    buttonStepFive_GaitMenu = button((5,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (10,0),
                            frameWalkingRoutine, text="Step 5", bg=indi_blue, fg='white',
                            command = lambda j="5":[Alice_gait_training.config(image=alice_step_five),send_instruction(j,labelStateProcess,1,1),enable_buttons([buttonStepOne_GaitMenu]),disable_buttons([buttonStepThree_GaitMenu,buttonStepFour_GaitMenu])])
    create_grid(frameWalkingRoutine, [buttonStepOne_GaitMenu,buttonStepTwo_GaitMenu,buttonStepThree_GaitMenu,buttonStepFour_GaitMenu,buttonStepFive_GaitMenu],
                rows=6,columns=1)

    frameSteppingRoutine = frame((0,2), init_sticky, init_rowspan, init_columnspan, (30,0), init_ipadding,
                                     app, bg='white')
    buttonConfirmStand_GaitMenu = button((0,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (15,0),
                                 frameSteppingRoutine, text="Confirm Stand", bg=indi_purple, fg='white',
                                 command = lambda j="S" :[Alice_gait_training.config(image=alice_gait_training),send_instruction(j,labelStateProcess,1,1),enable_buttons([buttonStepOne_GaitMenu]),disable_buttons([buttonStepTwo_GaitMenu,buttonStepThree_GaitMenu,buttonStepFour_GaitMenu,buttonStepFive_GaitMenu])])
    create_grid(frameSteppingRoutine, [buttonConfirmStand_GaitMenu],
                rows=3, columns=1)

def init_standing_exercises_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global buttonLeftBackwards, buttonLeftForwards
    global buttonRightBackwards, buttonRightForwards
    
    buttonLeftBackwards = button((1,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (15,0),
                           frameLeftLeg, text="Backwards", bg=indi_blue, fg='white',
                           command = lambda j="A": [Alice_standing_exercises.config(image=alice_left_backwards), send_instruction(j,labelStateProcess,1,1), enable_buttons([buttonConfirmStand], button_color=indi_purple), disable_buttons([buttonLeftBackwards,buttonLeftForwards,buttonRightBackwards,buttonRightForwards])])
    buttonLeftForwards = button((2,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (20,0),
                                frameLeftLeg,text="Forwards", bg=indi_blue, fg='white',
                                command=lambda j="B": [Alice_standing_exercises.config(image=alice_left_forwards), send_instruction(j,labelStateProcess,1,1), enable_buttons([buttonConfirmStand], button_color=indi_purple), disable_buttons([buttonLeftBackwards,buttonLeftForwards,buttonRightBackwards,buttonRightForwards])])
    buttonRightBackwards = button((1,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (15,0),
                           frameRightLeg, text="Backwards", bg=indi_blue, fg='white',
                           command = lambda j="C": [Alice_standing_exercises.config(image=alice_right_backwards), send_instruction(j,labelStateProcess,1,1), enable_buttons([buttonConfirmStand], button_color=indi_purple), disable_buttons([buttonLeftBackwards,buttonLeftForwards,buttonRightBackwards,buttonRightForwards])])
    buttonRightForwards = button((2,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (20,0),
                                frameRightLeg,text="Forwards", bg=indi_blue, fg='white',
                                command=lambda j="D": [Alice_standing_exercises.config(image=alice_right_forwards), send_instruction(j,labelStateProcess,1,1), enable_buttons([buttonConfirmStand], button_color=indi_purple), disable_buttons([buttonLeftBackwards,buttonLeftForwards,buttonRightBackwards,buttonRightForwards])])

def init_sitting_exercises_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding):
    global buttonLeftBend, buttonLeftExtend
    global buttonRightBend, buttonRightExtend
    global frameBothLegs, labelBothLegs, buttonBothBend, buttonBothExtend
    
    buttonLeftBend = button((2,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (20,0),
                           frameLeftLeg, text="Bend", bg=indi_blue, fg='white',
                           command = lambda j="E": [Alice_sitting_exercises.config(image=alice_left_bend), send_instruction(j,labelStateProcess,1,1)])
    buttonLeftExtend = button((1,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (15,0),
                                frameLeftLeg,text="Extend", bg=indi_blue, fg='white',
                                command=lambda j="F": [Alice_sitting_exercises.config(image=alice_left_extend), send_instruction(j,labelStateProcess,1,1)])

    buttonRightBend = button((2,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (20,0),
                           frameRightLeg, text="Bend", bg=indi_blue, fg='white',
                           command = lambda j="G": [Alice_sitting_exercises.config(image=alice_right_bend), send_instruction(j,labelStateProcess,1,1)])
    buttonRightExtend = button((1,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (15,0),
                                frameRightLeg,text="Extend", bg=indi_blue, fg='white',
                                command=lambda j="H": [Alice_sitting_exercises.config(image=alice_right_extend), send_instruction(j,labelStateProcess,1,1)])
    
    frameBothLegs = frame(init_position, init_sticky, init_rowspan, init_columnspan, (0,20), init_ipadding,
                         app, bg='white')
    labelBothLegs = label((0,0), init_sticky, init_rowspan, 2, init_padding, init_ipadding,
                         size=10, master=frameBothLegs, text='BOTH LEGS', bg='white', fg=indi_blue)
    buttonBothBend = button((1,1), init_sticky, init_rowspan, init_columnspan, init_button_padding, (20,0),
                           frameBothLegs, text="Bend", bg=indi_blue, fg='white',
                           command = lambda j="I": [Alice_sitting_exercises.config(image=alice_both_bend), send_instruction(j,labelStateProcess,1,1)])
    buttonBothExtend = button((1,0), init_sticky, init_rowspan, init_columnspan, init_button_padding, (15,0),
                           frameBothLegs, text="Extend", bg=indi_blue, fg='white',
                           command = lambda j="J": [Alice_sitting_exercises.config(image=alice_both_extend), send_instruction(j,labelStateProcess,1,1)])
    create_grid(frameBothLegs, [labelBothLegs, buttonBothBend, buttonBothExtend],
                rows=2, columns=2)
    
def waiting_for_connection():
    #### Grid ####
    mainMenuTitle.position = (0,0)
    labelStateProcess.position = (1,0)
    Alice_not_connected.position = (2,0)
    frameConnection.position = (3,0)
    frameBottom.position = (4,0)
    create_grid(app, [mainMenuTitle,labelStateProcess,Alice_not_connected,frameConnection,frameBottom],
                rows=5, columns=1)

def straight_menu():
    for child in app.winfo_children():
        child.grid_forget()
    for child_bottom in frameBottom.winfo_children():
        child_bottom.grid_forget()
        
    send_instruction("M",labelStateProcess,0,0)
        
    frameConnectionBottom.position = (0,0)
    frameBottomButtons.position, frameBottomButtons.sticky = (0,2), 'e'
    frameConnectionBottom.sticky = 'w'
    create_grid(frameBottom, [frameConnectionBottom, frameBottomButtons, labelCopyright],
                rows=2, columns=3)

    #### Grid ####
    mainMenuTitle.position, mainMenuTitle.columnspan = (0,0), 2
    labelStateProcess.position, labelStateProcess.columnspan = (1,0), 2
    Alice_stand_waiting.position, Alice_stand_waiting.columnspan = (2,0), 1
    Alice_sit_waiting.position, Alice_sit_waiting.columnspan = (2,1), 1
    buttonConfirmStand_StraightMenu.position, buttonConfirmStand_StraightMenu.columnspan = (3,0), 1
    buttonConfirmSit_StraightMenu.position, buttonConfirmSit_StraightMenu.columnspan = (3,1), 1
    frameBottom.position, frameBottom.columnspan = (4,0), 2
    create_grid(app, [mainMenuTitle,labelStateProcess,Alice_stand_waiting, Alice_sit_waiting, buttonConfirmStand_StraightMenu, buttonConfirmSit_StraightMenu, frameBottom],
                rows=5, columns=2)

    send_instruction("1",labelStateProcess,0,0)

def stand_menu():
    for child in app.winfo_children():
        child.grid_forget()
    for child_bottom in frameBottom.winfo_children():
        child_bottom.grid_forget()
    send_instruction("M",labelStateProcess,0,0)

    frameBottomButtons.position, frameBottomButtons.sticky = (1,2), 'e'
    frameConnectionBottom.sticky, buttonHome.sticky = 'w', 'e'
    create_grid(frameBottom, [frameConnectionBottom, buttonHome, labelCopyright, frameBottomButtons], 
                rows=2, columns=3)
    buttonConfirmStand.padding, buttonConfirmStand.ipadding = (40,10), (50,0)

    #### Grid ####
    mainMenuTitle.position, mainMenuTitle.columnspan = (0,0), 2
    labelStateProcess.position, labelStateProcess.columnspan = (1,0), 2
    Alice_stand_straight.position, Alice_stand_straight.sticky, Alice_stand_straight.rowspan = (2,0), 'e', 2
    buttonConfirmStand.position, buttonConfirmStand.sticky = (2,1), 'sw'
    frameStandButtons.position, frameStandButtons.sticky = (3,1), 'nw'
    frameStandMenus.position, frameStandMenus.columnspan = (4,0), 2
    frameBottom.position, frameBottom.columnspan = (5,0), 2
    create_grid(app, [mainMenuTitle,labelStateProcess,Alice_stand_straight,buttonConfirmStand,frameStandButtons,frameStandMenus,frameBottom],
                rows=6, columns=2)

    send_instruction("2",labelStateProcess,0,0)

def sit_menu():
    for child in app.winfo_children():
        child.grid_forget()
    for child_bottom in frameBottom.winfo_children():
        child_bottom.grid_forget()

    send_instruction("M",labelStateProcess,0,0)

    frameBottomButtons.position, frameBottomButtons.sticky = (1,2), 'e'
    frameConnectionBottom.sticky, buttonHome.sticky = 'w', 'e'
    create_grid(frameBottom, [frameConnectionBottom, buttonHome, labelCopyright, frameBottomButtons], 
                rows=2, columns=3)

    buttonConfirmSit.padding, buttonConfirmSit.ipadding = (40,10), (35,0)
    buttonSitToStand_SitMenu.padding = (40,10)

    #### Grid ####
    mainMenuTitle.position, mainMenuTitle.columnspan = (0,0), 2
    labelStateProcess.position, labelStateProcess.columnspan = (1,0), 2
    Alice_sit_straight.position, Alice_sit_straight.sticky, Alice_sit_straight.rowspan = (2,0), 'e', 2
    buttonConfirmSit.position, buttonConfirmSit.sticky = (2,1), 'sw'
    buttonSitToStand_SitMenu.position, buttonSitToStand_SitMenu.sticky = (3,1), 'nw'
    frameSitMenus.position, frameSitMenus.columnspan = (4,0), 2
    frameBottom.position, frameBottom.columnspan = (5,0), 2
    create_grid(app, [mainMenuTitle,labelStateProcess,Alice_sit_straight,buttonConfirmSit,buttonSitToStand_SitMenu,frameSitMenus,frameBottom],
                rows=6, columns=2)

    send_instruction("3",labelStateProcess,0,0)

def gait_training_menu():
    for child in app.winfo_children():
        child.grid_forget()
    for child_bottom in frameBottom.winfo_children():
        child_bottom.grid_forget()
        
    send_instruction("M",labelStateProcess,0,0)
        
    Alice_gait_training.config(image=alice_gait_training)
    frameBottomButtons.position, frameBottomButtons.sticky = (1,2), 'e'
    frameConnectionBottom.sticky, buttonHome.sticky = 'w', 'e'
    create_grid(frameBottom, [frameConnectionBottom, buttonHome, labelCopyright, frameBottomButtons], 
                rows=2, columns=3)
    
    #### Grid ####
    mainMenuTitle.position, mainMenuTitle.columnspan = (0,0), 3
    labelStateProcess.position, labelStateProcess.columnspan = (1,0), 3
    frameWalkingRoutine.position, Alice_gait_training.position, frameSteppingRoutine.position = (2,0), (2,1), (2,2)
    frameBottom.position, frameBottom.columnspan = (3,0), 3
    create_grid(app, [mainMenuTitle,labelStateProcess,frameWalkingRoutine, Alice_gait_training, frameSteppingRoutine,frameBottom],
                rows=4, columns=1)
    
    enable_buttons([buttonStepOne_GaitMenu])
    disable_buttons([buttonStepTwo_GaitMenu,buttonStepThree_GaitMenu,buttonStepFour_GaitMenu,buttonStepFive_GaitMenu])
    
    send_instruction("4",labelStateProcess,0,0)

def standing_exercises_menu():
    for child in app.winfo_children():
        child.grid_forget()
    for child_bottom in frameBottom.winfo_children():
        child_bottom.grid_forget()
    for child_left in frameLeftLeg.winfo_children():
        child_left.grid_forget()
    for child_right in frameRightLeg.winfo_children():
        child_right.grid_forget()

    send_instruction("M",labelStateProcess,0,0)

    Alice_standing_exercises.config(image=alice_standing_exercises)
    frameBottomButtons.position, frameBottomButtons.sticky = (1,2), 'e'
    frameConnectionBottom.sticky, buttonHome.sticky = 'w', 'e'
    create_grid(frameBottom, [frameConnectionBottom, buttonHome, labelCopyright, frameBottomButtons], 
                rows=2, columns=3)
    create_grid(frameLeftLeg, [labelLeftLeg,buttonLeftBackwards,buttonLeftForwards],
                rows=3, columns=1)
    create_grid(frameRightLeg, [labelRightLeg,buttonRightBackwards,buttonRightForwards],
                rows=3, columns=1)
    
    buttonConfirmStand.reset()
    buttonConfirmStand.padding, buttonConfirmStand.ipadding = (0,20), (10,0)
    buttonConfirmStand.config(command = lambda j="S" : [Alice_standing_exercises.config(image=alice_standing_exercises), send_instruction(j,labelStateProcess,1,1), enable_buttons([buttonLeftBackwards,buttonLeftForwards,buttonRightBackwards,buttonRightForwards])])

    #### Grid ####
    mainMenuTitle.position, mainMenuTitle.columnspan = (0,0), 3
    labelStateProcess.position, labelStateProcess.columnspan = (1,0), 3
    frameLeftLeg.position, Alice_standing_exercises.position, frameRightLeg.position = (2,0), (2,1), (2,2)
    buttonConfirmStand.position, buttonConfirmStand.sticky, buttonConfirmStand.columnspan = (3,0), 'n', 3
    frameBottom.position, frameBottom.columnspan = (4,0), 3
    create_grid(app, [mainMenuTitle,labelStateProcess,buttonConfirmStand,frameLeftLeg,Alice_standing_exercises,frameRightLeg,frameBottom],
                rows=5, columns=3)
    
    send_instruction("5",labelStateProcess,0,0)
    
def sitting_exercises_menu():
    for child in app.winfo_children():
        child.grid_forget()
    for child_bottom in frameBottom.winfo_children():
        child_bottom.grid_forget()
    for child_left in frameLeftLeg.winfo_children():
        child_left.grid_forget()
    for child_right in frameRightLeg.winfo_children():
        child_right.grid_forget()

    send_instruction("M",labelStateProcess,0,0)

    Alice_sitting_exercises.config(image=alice_sitting_exercises)
    frameBottomButtons.position, frameBottomButtons.sticky = (1,2), 'e'
    frameConnectionBottom.sticky, buttonHome.sticky = 'w', 'e'
    create_grid(frameBottom, [frameConnectionBottom, buttonHome, labelCopyright, frameBottomButtons], 
                rows=2, columns=3)
    create_grid(frameLeftLeg, [labelLeftLeg,buttonLeftBend,buttonLeftExtend],
                rows=3, columns=1)
    create_grid(frameRightLeg, [labelRightLeg,buttonRightBend,buttonRightExtend],
                rows=3, columns=1)
    frameLeftLeg.padding, frameRightLeg.padding = (0,20), (0,20)
    
    buttonConfirmSit.reset()
    buttonConfirmSit.padding, buttonConfirmSit.ipadding, buttonConfirmSit.sticky = (0,20), (10,0), 'n'
    buttonConfirmSit.config(command = lambda j="Z" : [Alice_sitting_exercises.config(image=alice_sitting_exercises), send_instruction(j,labelStateProcess,1,1)])
    
    #### Grid ####
    mainMenuTitle.position, mainMenuTitle.columnspan = (0,0), 3
    labelStateProcess.position, labelStateProcess.columnspan = (1,0), 3
    buttonConfirmSit.position, buttonConfirmSit.columnspan = (2,0), 3
    frameLeftLeg.position, Alice_sitting_exercises.position, frameRightLeg.position = (3,0), (3,1), (3,2)
    frameBothLegs.position, frameBothLegs.columnspan = (4,0), 3
    frameBottom.position, frameBottom.columnspan = (5,0), 3
    create_grid(app, [mainMenuTitle,labelStateProcess,buttonConfirmSit,frameLeftLeg,Alice_sitting_exercises,frameRightLeg,frameBothLegs,frameBottom],
                rows=6, columns=3)
    
    send_instruction("6",labelStateProcess,0,0)

######################################This is the Main Section#########################################
#-------------------------------------Serial Port parameters------------------------------------------#
ser = serial.Serial()
#'/dev/cu.usbmodem14201'#For MAC the format is /dev/cu...
#'COM9'#For Windows the format is COM...
ser.baudrate = 38400
ser.timeout = 0
#-----------------------------------------------------------------------------------------------------#

#--------------------------------LSL information sending (Markers)------------------------------------#
# first create a new stream info (here we set the name to MyMarkerStream,
# the content-type to Markers, 1 channel, irregular sampling rate,
# and string-valued data) The last value would be the locally unique
# identifier for the stream as far as available, e.g.
# program-scriptname-subjectnumber (you could also omit it but interrupted
# connections wouldn't auto-recover). The important part is that the
# content-type is set to 'Markers', because then other programs will know how
#  to interpret the content
info = StreamInfo('Presentation', 'Markers', 1, 0, 'string', 'Presentation')

# next make an outlet
outlet = StreamOutlet(info)
marker_s = "Start"#marker for start of the movement
marker_f= "Finish"#marker for end of the movment.
#------------------------------------------------------------------------------------------------------#

app = create_window()

init_images(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_shared_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_straight_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_stand_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_sit_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_gait_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_standing_exercises_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)
init_sitting_exercises_menu_buttons(app, init_position, init_sticky, init_rowspan, init_columnspan, init_padding, init_ipadding)

waiting_for_connection()


app.protocol("WM_DELETE_WINDOW", _delete_window)

app.mainloop()
########################################################################################################

