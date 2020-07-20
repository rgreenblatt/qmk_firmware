import base64
import lzma
import os
import sys


def main():
    in_name = sys.argv[1]
    compressed = lzma.compress(open(in_name, 'rb').read())

    out_file_name = os.path.basename(in_name)
    print('''#!/usr/bin/env python3
import lzma
import base64
open('{}', 'wb').write(lzma.decompress(base64.b64decode('{}')))
'''.format(out_file_name, base64.b64encode(compressed).decode('utf-8')))


if __name__ == "__main__":
    main()
