# An attempt to replicate the Waytools Textblade layout.

I can't say it's accurate as I don't actually have a textblade, but this is mostly based off of videos and pictures available on their site [Waytools.com](http://waytools.com). Made this so I could practice before I got mine... (Not sure how many dots a 4 year ellipsis should contain)

I kept things simple (or compicated) with layer locking. When switching to a layer with a chord, just double tap the last key while holding the first. For example, hold down D and F and keep holding to switch to the Edit layer. To lock the Edit layer, hold down either D or F and double tap the other key. To exit a layer lock, just hit CapsLock.

## ToDo:
 - Improve timings - if something is held down when typing the next key, then things get sketchy. Seems to work best for me when I'm typing quickly. If I'm thinking too much and linger on a key or am lazy with releasing a letter before the next, the key gets eaten (because of a temporary layer toggle).
 - Finish readme
 - Finish lighting layers (numlock)
 - Tidy Tidy Tidy the code

## Not implemented:
 - Locking out keys on held down pads/keys. On the actual Textblade with QWERTY layout, LeftShift and A are on the same 'pad' and could not be used together. Which in my case means I'll
 still have some bad habits.
 - Jumps, thankfully I don't have a bluetooth keyboard to jump down this rabbit hole of code.
 - Placement of ` and ~, I've put them on the leftShift under the space layer. It still works as leftShift when held down.
 - Placement of | is just a shifted \ under the space layer.
 
## Implemented but not on Textblade (that I know of):
 - Emergency mouse, hold space and tap capslock. Hope they do this on the real one.

## Qwerty
```
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |Enter |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Lower| Raise|Backlt|      | Space| Space|Space |Space |      |      |      |      |
`-----------------------------------------------------------------------------------'
 ```

## Edit
```
,-----------------------------------------------------------------------------------.
| Tab  |      |      |      |      |      | CUT  |CTL_LF|  UP  |CTL_RT|CTRL_A| Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| EXITL|ToMDIA| SHIFT|-HOLD-|-HOLD-|      | COPY | LEFT | DOWN | RIGHT| UNDO |Enter |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|      |      |      |      |      | PASTE| HOME | DOWN | END  | REDO |Shift |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Lower| Raise|Backlt|      | Space| Space|Space |Space |      |      |      |      |
`-----------------------------------------------------------------------------------'
```

## Space
```
,-----------------------------------------------------------------------------------.
| ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | DEL  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|ToMOUS|   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |Enter |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   +  |   -  |   =  |   {  |   }  |   [  |   ]  |   ;  |   .  |   /  |Shift |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Lower| Raise|Backlt|      |HOLD 1|HOLD 1|HOLD 1|HOLD 1|      |      |      |      |
`-----------------------------------------------------------------------------------'
```

