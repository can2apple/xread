#include <stdio.h>
#include <stdlib.h>
#include "../src/xread.h"

void handler(xr_type type, xr_str name, xr_str val) {
    switch (type) {
        case xr_type_element:
        case xr_type_element_end:
        case xr_type_attribute:
        case xr_type_cdata:
        case xr_type_comment:
        case xr_type_doctype:
        case xr_type_proc_instr:
        case xr_type_text:
        case xr_type_xml_decl:
            return;
        case xr_type_error:
            exit(1);
            return;
    }
}

int main() {
    FILE* fp = fopen("test/test.xml", "rb");
    if (!fp) return 1;
    fseek(fp, 0, SEEK_END);
    int32_t size = (int32_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*)malloc(size + 1);
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    fclose(fp);
    xr_read(&handler, buffer);
    free(buffer);
}

