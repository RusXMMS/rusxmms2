/* I tried to use it to fix broken tags (call id3_get_text), but
it really didn't help much (half of title tag, instead of one fourth) */
void id3_fix_text(struct id3_frame *frame, int offset) {
    int i, size;
    char *string;
    
    size = frame->fr_size - offset - 1;
    string = ID3_TEXT_FRAME_PTR(frame) + offset;
    
    for (offset=0, i=0;i<size;i++) {
	if (!string[i]) offset++;
	else if (offset) string[i-offset] = string[i];
    }

    for (;offset>0;offset--) string[i-offset]=0;
}
