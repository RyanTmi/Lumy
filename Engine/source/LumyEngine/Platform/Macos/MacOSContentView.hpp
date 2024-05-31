#pragma once

#import <AppKit/NSView.h>
#import <AppKit/NSTextInputClient.h>

@class MacOSWindow;

@interface MacOSContentView : NSView <NSTextInputClient>
{
    MacOSWindow* window;
    NSTrackingArea* trackingArea;
    NSMutableAttributedString* markedText;
}

- (instancetype)initWithWindow:(MacOSWindow*)initWindow frame:(NSRect)initFrame;

@end
