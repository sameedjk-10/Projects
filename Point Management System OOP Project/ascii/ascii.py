from time import sleep
import pyfiglet

with open("ascii_pyfigletfonts.txt", "r") as file:
    fonts = file.read().splitlines()

text = input("Enter the text to convert to ascii: ")
my_font = input("Input required font or 0 to print in all formats: ")

with open("text.txt", "w") as File:
    if my_font == '0':
        for fonty in fonts:
            Figlet = pyfiglet.Figlet(font=fonty)
            print(fonty,"\n", Figlet.renderText(text) ,file=File)
            print("\n\n\n", file=File)
    
    elif my_font in fonts:
        Figlet = pyfiglet.Figlet(font = my_font)
        print(my_font ,"\n", Figlet.renderText(text) ,file=File)
        
