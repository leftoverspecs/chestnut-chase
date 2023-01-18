from sys import argv


HEADER = '''\
#pragma once

static const unsigned char {name}[] = {{
    {content}
}};
'''

def main():
    infile = argv[1]
    name = argv[2]
    outfile = argv[3]
    with open(infile, 'rb') as f:
        content = f.read()
    lines = [', '.join(['0x{:02x}'.format(b) for b in content[i:i+16]]) for i in range(0, len(content), 16)]
    with open(outfile, 'w') as f:
        f.write(HEADER.format(name=name, content=',\n    '.join(lines)))


if __name__ == '__main__':
    main()
