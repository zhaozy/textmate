#import <OakAppKit/OakFileIconImage.h>
#import <OakAppKit/NSImage Additions.h>
#import <test/cocoa.h>
#import <oak/oak.h>

@interface MyImageView : NSView
{
	NSImage* image;
}
@property (nonatomic, retain) NSImage* image;
@end

@implementation MyImageView
@synthesize image;

- (void)drawRect:(NSRect)aRect
{
	NSEraseRect(aRect);
	if(!image)
		self.image = [OakFileIconImage fileIconImageWithPath:NSHomeDirectory() size:NSMakeSize(16, 16)];
	[self.image drawAdjustedInRect:NSMakeRect(0, 0, NSWidth(self.frame), NSHeight(self.frame)) fromRect:NSZeroRect operation:NSCompositeSourceOver fraction:1];
}
@end

class ResizeImageTests : public CxxTest::TestSuite
{
public:
	void test_resize_image ()
	{
		OakSetupApplicationWithView([[MyImageView alloc] initWithFrame:NSMakeRect(0, 0, 200, 50)], "resize_image");
	}
};
