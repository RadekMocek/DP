package main

import (
	"log"
	"os"
	"strconv"

	"gioui.org/app"
	"gioui.org/layout"
	"gioui.org/op"
	"gioui.org/unit"
	"gioui.org/widget"
	"gioui.org/widget/material"
)

type C = layout.Context
type D = layout.Dimensions

func main() {
	go func() {
		window := new(app.Window)

		window.Option(app.Title("Gio :: ConceptA"))

		err := run(window)
		if err != nil {
			log.Fatal(err)
		}
		os.Exit(0)
	}()
	app.Main()
}

func run(window *app.Window) error {
	theme := material.NewTheme()

	// Ops are the operations from the UI
	var ops op.Ops

	// Widgets
	var buttonMinus widget.Clickable
	var buttonPlus widget.Clickable

	// State
	counter := 1

	for {
		switch e := window.Event().(type) {

		case app.DestroyEvent:
			return e.Err

		case app.FrameEvent:
			// This graphics context is used for managing the rendering state.
			gtx := app.NewContext(&ops, e)

			// Update state
			if buttonMinus.Clicked(gtx) && counter > 1 {
				counter--
			}

			if buttonPlus.Clicked(gtx) && counter < 5 {
				counter++
			}

			// Draw
			layout.Inset{
				Top:    unit.Dp(16),
				Bottom: unit.Dp(16),
				Left:   unit.Dp(16),
				Right:  unit.Dp(16),
			}.Layout(gtx, func(gtx C) D {
				return layout.Flex{
					Axis: layout.Vertical,
				}.Layout(gtx,
					layout.Rigid(func(gtx C) D {
						return layout.Flex{
							Axis: layout.Horizontal,
						}.Layout(gtx,
							layout.Rigid(
								func(gtx C) D {
									if counter == 1 {
										gtx = gtx.Disabled()
									}
									btn := material.Button(theme, &buttonMinus, "-")
									return btn.Layout(gtx)
								},
							),

							layout.Rigid(layout.Spacer{Width: unit.Dp(10)}.Layout),

							layout.Rigid(
								func(gtx C) D {
									label := material.Label(theme, 24, strconv.Itoa(counter))
									return label.Layout(gtx)
								},
							),

							layout.Rigid(layout.Spacer{Width: unit.Dp(10)}.Layout),

							layout.Rigid(
								func(gtx C) D {
									if counter == 5 {
										gtx = gtx.Disabled()
									}
									btn := material.Button(theme, &buttonPlus, "+")
									return btn.Layout(gtx)
								},
							),
						)
					}),

					layout.Rigid(layout.Spacer{Width: unit.Dp(10)}.Layout),

					layout.Rigid(func(gtx C) D {
						if counter == 3 {
							label := material.Label(theme, 24, "Hello!")
							return label.Layout(gtx)
						}
						return D{}
					}),
				)
			})

			// Pass the drawing operations to the GPU.
			e.Frame(gtx.Ops)
		}
	}
}
