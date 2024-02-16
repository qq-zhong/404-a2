import subprocess
import binascii     
def read_file_as_hex(filename):
    with open(filename, 'rb') as f:
        hex_string = binascii.hexlify(f.read()).decode('utf-8')
    return hex_string

def read_text_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        return [line.strip() for line in lines]

# Command to execute
command = [
    'openssl', 'enc', '-d', '-aes-128-cbc',
    '-iv', '00112233445566778899AABBCCDDEEFF',
    '-K', 'aa',
    '-in', 'fcfd5138503a.pdf.enc',
    '-out', 'result.pdf'
]

input_file = 'fcfd5138503a.pdf.enc'
output_file = 'result.pdf'
file_path = "strings.txt"

strings_list = read_text_file(file_path)
strings_list = ['FFEEDDCCBBAA99887766554433221100'] + strings_list
bad_count = 0

for index, a_key in enumerate(strings_list):
        #print(a_key)
    command[7] = a_key
    #print(command)
    # Execute the command
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Check if the command executed successfully
   
    
    hex_string = read_file_as_hex('result.pdf')
    #print(hex_string)
    #print(hex_string[32:48])
    if (hex_string[32:48] == "2030206f626a0a3c"):
        print(hex_string[32:48])
        break
    
    if result.returncode == 0:
        if index % 1000 == 0:
            print(index)
    else:
        bad_count = bad_count + 1;
        if bad_count%10 == 0:
            print(bad_count)