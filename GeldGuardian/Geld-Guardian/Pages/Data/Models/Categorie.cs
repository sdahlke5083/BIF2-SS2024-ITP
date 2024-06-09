using Microsoft.EntityFrameworkCore;

namespace Geld_Guardian.Pages.Data.Models
{
    [PrimaryKey("CategorieId")]
    public class Categorie
    {
        public int CategorieId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
    }
}
