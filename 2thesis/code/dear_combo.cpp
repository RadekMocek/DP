constexpr std::array node_types = {
    ICON_MDI_RECTANGLE_OUTLINE" Rectangle",
    ICON_MDI_ELLIPSE_OUTLINE" Ellipse",
    ICON_MDI_RHOMBUS_OUTLINE" Diamond",
    ICON_MDI_FORMAT_TEXT_VARIANT" Text"
};
static int idx; // Index právě vybrané položky v rozbalovacím seznamu

ImGui::PushItemWidth(160); // Nastavení šířky ovládacího prvku
if (GUICombo("##ComboNodeType", node_types, idx))
    { /* Uživatel vybral jinou položku */ }
ImGui::PopItemWidth();