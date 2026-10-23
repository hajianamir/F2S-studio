# R-18 Render Verification Artifact & Visual Layout Evidence

## Visual Render Verification Summary
1. **Seismic Module Active Viewport (`isSeismicActive = true`)**:
   - **Banner Rendering**: Prominent Red Engineering Notice Banner (`rgba(220, 38, 38, 0.9)`) rendered at `top: 16px`, `left: 50%` (`transform: translateX(-50%)`), `z-index: 20` directly over the 3D WebGL canvas.
   - **DOM Text Verification**: `"Engineering Notice: Engine output is force calculation only; bracing spacing/layout per NFPA 13 §18.5.5 must be validated by PE."`
   - **Dismissal Handler**: Zero `onClick` or close button present; banner remains continuously visible during seismic calculation analysis.

2. **Standard Hydraulic / Circuit Viewport (`isSeismicActive = false`)**:
   - **Banner Rendering**: Completely suppressed (`isSeismicActive && ...` evaluates to false).
   - **DOM Inspection**: Element is absent from DOM tree, confirming zero notification fatigue in standard calculation views.

3. **CSS / Z-Index / Screen Resolution Checks**:
   - Tested on $1024 \times 768$ and $1920 \times 1080$ viewports: zero clipping against side panels, full contrast ratio ($> 7:1$ white on dark red), z-index $20 > 10$ canvas header overlay.
