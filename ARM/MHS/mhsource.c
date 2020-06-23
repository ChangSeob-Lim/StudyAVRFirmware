#define RCC             0x40023800
#define RCC_AHB1ENR     *((unsigned int*)(RCC + 0x30))     // 0x40023830

#define GPIOC           0x40020800
#define GPIOC_MODER     *((unsigned int*)(GPIOC + 0x00))   // 0x40020800
#define GPIOC_OTYPER    *((unsigned int*)(GPIOC + 0x04))   // 0x40020804
#define GPIOC_OSPEEDR   *((unsigned int*)(GPIOC + 0x08))   // 0x40020808
#define GPIOC_PUPDR     *((unsigned int*)(GPIOC + 0x0c))   // 0x4002080c
#define GPIOC_IDR       *((unsigned int*)(GPIOC + 0x10))   // 0x40020810
#define GPIOC_ODR       *((unsigned int*)(GPIOC + 0x14))   // 0x40020814

static void Delay(const unsigned int count)
{
  unsigned int i = 0;
  for(i = (5000 * count); i != 0; i--);
}

int main()
{
  RCC_AHB1ENR = 0x00000004;     // PORT clock enable
  GPIOC_MODER = 0x00000055;     // PORT[3:0] OUTPUT
  GPIOC_OTYPER = 0x0000000;     // push-pull
  GPIOC_OSPEEDR = 0x00000000;   // SPEED
  GPIOC_PUPDR = 0x00000000;     // No Pull-up / Pull-down
  
  while(1)
  {
    GPIOC_ODR = 0x0005; // 0, 2 ON 1, 3 OFF
    Delay(1000);
    GPIOC_ODR = 0x000A; // 1, 3 ON 0, 2 OFF
    Delay(1000);
  }
}