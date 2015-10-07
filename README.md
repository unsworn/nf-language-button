# Language Button

Arduino sketch powering the [nf-birdstories](https://github.com/unsworn/nf-birdstories) station

## Functionality

### Language button

When a user pushes the button the <kbd>l</kbd> key is clicked and released by the Arduino (software) keyboard. This 

### Pointer lock engagement gesture

Also, to enable pointer lock on nf-birdstories the <kbd>p</kbd> key is triggered every 10 seconds for 10 minutes after bootup.

Administrators can manually trigger the engagement gesture by pressing and holding the language button for 3 seconds. This will also cancel the automatic, recurring engagement gesture sequence.

## Notes

Made for Arduino Leonardo
