import customtkinter as ctk
from PIL import Image


def rotor_error(rotor_num):
    my_image = ctk.CTkImage(dark_image=Image.open("files/rotor_red.png"), size=(140, 120))
    if rotor_num == 1:
        rotor_panel1 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
        rotor_panel1.grid(row=0, column=0, padx=(0, 80), pady=(0, 80))
    if rotor_num == 2:
        rotor_panel2 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
        rotor_panel2.grid(row=0, column=1, pady=(0, 80))
    if rotor_num == 3:
        rotor_panel3 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
        rotor_panel3.grid(row=1, column=0, padx=(0, 80))
    if rotor_num == 4:
        rotor_panel4 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
        rotor_panel4.grid(row=1, column=1)


ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

root = ctk.CTk()
root.geometry("1000x600")

mainframe = ctk.CTkFrame(root)
mainframe.pack()

label = ctk.CTkLabel(mainframe, text="Quadcopter Live Monitoring")
label.pack()

rotor_frame = ctk.CTkFrame(mainframe)
rotor_frame.pack()

my_image = ctk.CTkImage(dark_image=Image.open("files/rotor_green.png"), size=(140, 120))
rotor_panel1 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
rotor_panel1.grid(row=0, column=0, padx=(0, 80), pady=(0, 80))
rotor_panel2 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
rotor_panel2.grid(row=0, column=1, pady=(0, 80))
rotor_panel3 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
rotor_panel3.grid(row=1, column=0, padx=(0, 80))
rotor_panel4 = ctk.CTkLabel(rotor_frame, image=my_image, text="")
rotor_panel4.grid(row=1, column=1)

rotor_error(1)
rotor_error(4)

root.mainloop()


