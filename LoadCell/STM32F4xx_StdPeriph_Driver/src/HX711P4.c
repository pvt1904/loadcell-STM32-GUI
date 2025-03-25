#include <HX711P4.h>

void hx711_init(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *data_gpio, uint16_t data_pin)
{
  // Setup the pin connections with the STM32 Board
  hx711->clk_gpio = clk_gpio;
  hx711->clk_pin = clk_pin;
  hx711->data_gpio = data_gpio;
  hx711->data_pin = data_pin;

  GPIO_InitTypeDef GPIO_InitStructure;

  // Enable the clock for the GPIO ports
  if (clk_gpio == GPIOA)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  if (clk_gpio == GPIOB)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  if (clk_gpio == GPIOC)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  if (clk_gpio == GPIOD)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  if (clk_gpio == GPIOE)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  if (clk_gpio == GPIOF)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  if (clk_gpio == GPIOG)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  if (clk_gpio == GPIOH)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
  if (clk_gpio == GPIOI)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

  if (data_gpio == GPIOA)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  if (data_gpio == GPIOB)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  if (data_gpio == GPIOC)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  if (data_gpio == GPIOD)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  if (data_gpio == GPIOE)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  if (data_gpio == GPIOF)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  if (data_gpio == GPIOG)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  if (data_gpio == GPIOH)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
  if (data_gpio == GPIOI)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

  /* Configure clock */
  GPIO_InitStructure.GPIO_Pin = clk_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(clk_gpio, &GPIO_InitStructure);

  /* Configure data */
  GPIO_InitStructure.GPIO_Pin = data_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(data_gpio, &GPIO_InitStructure);
}

void delay_us(uint16_t period)
{

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  TIM6->PSC = 83; // clk = SystemCoreClock /2/(PSC+1) = 1MHz
  TIM6->ARR = period - 1;
  TIM6->CNT = 0;
  TIM6->EGR = 1; // update registers;

  TIM6->SR = 0;  // clear overflow flag
  TIM6->CR1 = 1; // enable Timer6

  while (!TIM6->SR)
    ;

  TIM6->CR1 = 0; // stop Timer6
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}

void IntToStr6(int32_t u, uint8_t *y)
{
  int32_t a;
  a = u;
  if (a < 0)
  {
    a = -a;
    y[0] = '-';
  }
  else
    y[0] = ' ';
  y[5] = a % 10 + 0x30;
  a = a / 10;
  y[4] = a % 10 + 0x30;
  a = a / 10;
  y[3] = a % 10 + 0x30;
  a = a / 10;
  y[2] = a % 10 + 0x30;
  a = a / 10;
  y[1] = a + 0x30;
}

int32_t Str6ToInt(const uint8_t *y)
{
  int32_t result = 0;
  int sign = 1;

  if (y[0] == '-')
  {
    sign = -1;
  }
  else if (y[0] != ' ')
  {
    return 0; // Invalid format
  }

  // Convert characters to integer, ignoring the sign character
  for (int i = 1; i < 6; i++)
  {
    if (y[i] < '0' || y[i] > '9')
    {
      return 0; // Invalid digit
    }
    result = result * 10 + (y[i] - '0');
  }

  return sign * result;
}

int32_t update(hx711_t *hx711, int32_t A0, int32_t A1, int32_t M0, int32_t M1)
{
  uint8_t dout = 0;
	int32_t data = 0;
  while (GPIO_ReadInputDataBit(hx711->data_gpio, hx711->data_pin) != Bit_RESET){}
  for (uint8_t i = 0; i < (24 + 1); i++)
  { // read 24 bit data + set gain and start next conversion
    GPIO_SetBits(hx711->clk_gpio, hx711->clk_pin);
    delay_us(2);
    GPIO_ResetBits(hx711->clk_gpio, hx711->clk_pin);
    delay_us(2);
    if (i < (24))
    {
      dout = GPIO_ReadInputDataBit(hx711->data_gpio, hx711->data_pin) == Bit_SET ? 1 : 0;
      data = (data << 1) | dout;
    }
  }
  uint32_t mask = (data & (1 << 23)) ? 0xFF000000 : 0x00000000;
  data = (data & 0x00FFFFFF) | mask;
	return data;
  //return (data - A0) * (M1 - M0) / (A1 - A0) + M0;
}

int32_t read_average(hx711_t *hx711, int32_t A0, int32_t A1, int32_t M0, int32_t M1, int sample_time) {
    if (sample_time <= 2) {
        int32_t data = update(hx711, A0, A1, M0, M1);
        return (data - A0) * (M1 - M0) / (A1 - A0) + M0;
    }

    int64_t sum = 0;
    int32_t largest = INT32_MIN;
    int32_t smallest = INT32_MAX;
    int32_t data = 0;

    for (int i = 0; i < sample_time; i++) {
        data = update(hx711, A0, A1, M0, M1);
        sum += data;

        if (data > largest) largest = data;
        if (data < smallest) smallest = data;
    }

    sum -= largest;
    sum -= smallest;

    int32_t average = sum / (sample_time - 2);
		return average;
    //return (average - A0) * (M1 - M0) / (A1 - A0) + M0;
}
