#pragma once

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface MacOSWindowController : NSWindowController<NSWindowDelegate>

- (void)windowDidResize:(NSNotification *)notification;

- (void)windowDidMiniaturize:(NSNotification *)notification;

- (void)windowDidDeminiaturize:(NSNotification *)notification;

- (void)windowDidChangeScreen:(NSNotification *)notification;

- (BOOL)windowShouldClose:(NSWindow *)sender;

@end
